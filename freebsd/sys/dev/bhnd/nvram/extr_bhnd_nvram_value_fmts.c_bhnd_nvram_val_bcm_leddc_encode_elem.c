#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  led32 ;
typedef  int /*<<< orphan*/  led16 ;
typedef  int /*<<< orphan*/  ival ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_STRING 130 
#define  BHND_NVRAM_TYPE_UINT16 129 
#define  BHND_NVRAM_TYPE_UINT32 128 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int /*<<< orphan*/ ) ; 
 int EFTYPE ; 
 int ENOMEM ; 
 int ERANGE ; 
 int UINT16_MAX ; 
 int UINT32_MAX ; 
 int bhnd_nvram_parse_int (char const*,size_t,int /*<<< orphan*/ ,size_t*,int*,size_t*,int) ; 
 int /*<<< orphan*/  bhnd_nvram_type_name (int) ; 
 int bhnd_nvram_val_elem_type (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,int,void*,size_t*,int) ; 
 int bhnd_nvram_value_printf (char*,int*,int,int,void*,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_leddc_encode_elem(bhnd_nvram_val *value, const void *inp,
    size_t ilen, void *outp, size_t *olen, bhnd_nvram_type otype)
{
	bhnd_nvram_type		itype;
	size_t			limit, nbytes;
	int			error;
	uint16_t		led16;
	uint32_t		led32;
	bool			led16_lossy;
	union {
		uint16_t	u16;
		uint32_t	u32;
	} strval;

	/*
	 * LED duty-cycle values represent the on/off periods as a 32-bit
	 * integer, with the top 16 bits representing on cycles, and the
	 * bottom 16 representing off cycles.
	 * 
	 * LED duty cycle values have three different formats:
	 * 
	 * - SPROM:	A 16-bit unsigned integer, with on/off cycles encoded
	 *		as 8-bit values.
	 * - NVRAM:	A 16-bit decimal or hexadecimal string, with on/off
	 *		cycles encoded as 8-bit values as per the SPROM format.
	 * - NVRAM:	A 32-bit decimal or hexadecimal string, with on/off
	 *		cycles encoded as 16-bit values.
	 *
	 * To convert from a 16-bit representation to a 32-bit representation:
	 *     ((value & 0xFF00) << 16) | ((value & 0x00FF) << 8)
	 * 
	 * To convert from a 32-bit representation to a 16-bit representation,
	 * perform the same operation in reverse, discarding the lower 8-bits
	 * of each half of the 32-bit representation:
	 *     ((value >> 16) & 0xFF00) | ((value >> 8) & 0x00FF)
	 */

	itype = bhnd_nvram_val_elem_type(value);
	nbytes = 0;
	led16_lossy = false;

	/* Determine output byte limit */
	if (outp != NULL)
		limit = *olen;
	else
		limit = 0;

	/* If the input/output types match, just delegate to standard value
	 * encoding support */
	if (otype == itype) {
		return (bhnd_nvram_value_coerce(inp, ilen, itype, outp, olen,
		    otype));
	}

	/* If our value is a string, it may either be a 16-bit or a 32-bit
	 * representation of the duty cycle */
	if (itype == BHND_NVRAM_TYPE_STRING) {
		const char	*p;
		uint32_t	 ival;
		size_t		 nlen, parsed;

		/* Parse integer value */
		p = inp;
		nlen = sizeof(ival);
		error = bhnd_nvram_parse_int(p, ilen, 0, &parsed, &ival, &nlen,
		    BHND_NVRAM_TYPE_UINT32);
		if (error)
			return (error);

		/* Trailing garbage? */
		if (parsed < ilen && *(p+parsed) != '\0')
			return (EFTYPE);

		/* Point inp and itype to either our parsed 32-bit or 16-bit
		 * value */
		inp = &strval;
		if (ival & 0xFFFF0000) {
			strval.u32 = ival;
			itype = BHND_NVRAM_TYPE_UINT32;
		} else {
			strval.u16 = ival;
			itype = BHND_NVRAM_TYPE_UINT16;
		}
	}

	/* Populate both u32 and (possibly lossy) u16 LEDDC representations */
	switch (itype) {
	case BHND_NVRAM_TYPE_UINT16: {
		led16 = *(const uint16_t *)inp;
		led32 = ((led16 & 0xFF00) << 16) | ((led16 & 0x00FF) << 8);

		/* If all bits are set in the 16-bit value (indicating that
		 * the value is 'unset' in SPROM), we must update the 32-bit
		 * representation to match. */
		if (led16 == UINT16_MAX)
			led32 = UINT32_MAX;

		break;
	}

	case BHND_NVRAM_TYPE_UINT32:
		led32 = *(const uint32_t *)inp;
		led16 = ((led32 >> 16) & 0xFF00) | ((led32 >> 8) & 0x00FF);

		/*
		 * Determine whether the led16 conversion is lossy:
		 * 
		 * - If the lower 8 bits of each half of the 32-bit value
		 *   aren't set, we can safely use the 16-bit representation
		 *   without losing data.
		 * - If all bits in the 32-bit value are set, the variable is
		 *   treated as unset in  SPROM. We can safely use the 16-bit
		 *   representation without losing data.
		 */
		if ((led32 & 0x00FF00FF) != 0 && led32 != UINT32_MAX)
			led16_lossy = true;

		break;
	default:
		BHND_NV_PANIC("unsupported backing data type: %s",
		    bhnd_nvram_type_name(itype));
	}

	/*
	 * Encode as requested output type.
	 */
	switch (otype) {
	case BHND_NVRAM_TYPE_STRING:
		/*
		 * Prefer 16-bit format.
		 */
		if (!led16_lossy) {
			return (bhnd_nvram_value_printf("0x%04hX", &led16,
			    sizeof(led16), BHND_NVRAM_TYPE_UINT16, outp, olen));
		} else {
			return (bhnd_nvram_value_printf("0x%04X", &led32,
			    sizeof(led32), BHND_NVRAM_TYPE_UINT32, outp, olen));
		}

		break;

	case BHND_NVRAM_TYPE_UINT16: {
		/* Can we encode as uint16 without losing data? */
		if (led16_lossy)
			return (ERANGE);

		/* Write led16 format */
		nbytes += sizeof(uint16_t);
		if (limit >= nbytes)
			*(uint16_t *)outp = led16;

		break;
	}

	case BHND_NVRAM_TYPE_UINT32:
		/* Write led32 format */
		nbytes += sizeof(uint32_t);
		if (limit >= nbytes)
			*(uint32_t *)outp = led32;
		break;

	default:
		/* No other output formats are supported */
		return (EFTYPE);
	}

	/* Provide the actual length */
	*olen = nbytes;

	/* Report insufficient space (if output was requested) */
	if (limit < nbytes && outp != NULL)
		return (ENOMEM);

	return (0);
}
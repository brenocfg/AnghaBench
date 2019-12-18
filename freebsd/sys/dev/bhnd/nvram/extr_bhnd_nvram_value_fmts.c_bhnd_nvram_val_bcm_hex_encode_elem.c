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
typedef  int /*<<< orphan*/  sval ;
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_INT64 ; 
 scalar_t__ BHND_NVRAM_TYPE_STRING ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bhnd_nvram_is_int_type (scalar_t__) ; 
 scalar_t__ bhnd_nvram_is_signed_type (scalar_t__) ; 
 int bhnd_nvram_type_width (scalar_t__) ; 
 scalar_t__ bhnd_nvram_val_elem_type (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_generic_encode_elem (int /*<<< orphan*/ *,void const*,size_t,void*,size_t*,scalar_t__) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,scalar_t__,scalar_t__*,size_t*,scalar_t__) ; 
 int bhnd_nvram_value_printf (char*,void const*,size_t,scalar_t__,void*,size_t*,int) ; 

__attribute__((used)) static int
bhnd_nvram_val_bcm_hex_encode_elem(bhnd_nvram_val *value, const void *inp,
    size_t ilen, void *outp, size_t *olen, bhnd_nvram_type otype)
{
	bhnd_nvram_type	itype;
	ssize_t		width;
	int		error;

	itype = bhnd_nvram_val_elem_type(value);
	BHND_NV_ASSERT(bhnd_nvram_is_int_type(itype), ("invalid type"));

	/* If not encoding as a string, perform generic value encoding */
	if (otype != BHND_NVRAM_TYPE_STRING)
		return (bhnd_nvram_val_generic_encode_elem(value, inp, ilen,
		    outp, olen, otype));

	/* If the value is a signed, negative value, encode as a decimal
	 * string */
	if (bhnd_nvram_is_signed_type(itype)) {
		int64_t		sval;
		size_t		slen;
		bhnd_nvram_type	stype;

		stype = BHND_NVRAM_TYPE_INT64;
		slen = sizeof(sval);

		/* Fetch 64-bit signed representation */
		error = bhnd_nvram_value_coerce(inp, ilen, itype, &sval, &slen,
		    stype);
		if (error)
			return (error);

		/* Decimal encoding required? */
		if (sval < 0)
			return (bhnd_nvram_value_printf("%I64d", &sval, slen,
			    stype, outp, olen, otype));
	}

	/*
	 * Encode the value as a hex string.
	 * 
	 * Most producers of Broadcom NVRAM values zero-pad hex values out to
	 * their native width (width * two hex characters), and we do the same
	 * for compatibility
	 */
	width = bhnd_nvram_type_width(itype) * 2;
	return (bhnd_nvram_value_printf("0x%0*I64X", inp, ilen, itype,
	    outp, olen, width));
}
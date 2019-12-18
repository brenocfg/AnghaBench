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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  char uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  char u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_CHAR 136 
#define  BHND_NVRAM_TYPE_INT16 135 
#define  BHND_NVRAM_TYPE_INT32 134 
#define  BHND_NVRAM_TYPE_INT64 133 
#define  BHND_NVRAM_TYPE_INT8 132 
#define  BHND_NVRAM_TYPE_UINT16 131 
#define  BHND_NVRAM_TYPE_UINT32 130 
#define  BHND_NVRAM_TYPE_UINT64 129 
#define  BHND_NVRAM_TYPE_UINT8 128 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 int EFTYPE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 scalar_t__ INT16_MAX ; 
 scalar_t__ INT16_MIN ; 
 scalar_t__ INT32_MAX ; 
 scalar_t__ INT32_MIN ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ INT8_MAX ; 
 scalar_t__ INT8_MIN ; 
 scalar_t__ UINT16_MAX ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ UINT8_MAX ; 
 scalar_t__ bhnd_nv_isdigit (char) ; 
 int /*<<< orphan*/  bhnd_nv_isspace (char const) ; 
 scalar_t__ bhnd_nv_isupper (char) ; 
 scalar_t__ bhnd_nv_isxdigit (char) ; 
 int /*<<< orphan*/  bhnd_nvram_is_int_type (int) ; 
 size_t bhnd_nvram_type_width (int) ; 

int
bhnd_nvram_parse_int(const char *str, size_t maxlen,  u_int base,
    size_t *nbytes, void *outp, size_t *olen, bhnd_nvram_type otype)
{
	uint64_t	value;
	uint64_t	carry_max, value_max;
	uint64_t	type_max;
	size_t		limit, local_nbytes;
	size_t		ndigits;
	bool		negative, sign, twos_compl;

	/* Must be an integer type */
	if (!bhnd_nvram_is_int_type(otype))
		return (EINVAL);

	/* Determine output byte limit */
	if (outp != NULL)
		limit = *olen;
	else
		limit = 0;

	/* We always need a byte count. If the caller provides a NULL nbytes,
	 * track our position in a stack variable */
	if (nbytes == NULL)
		nbytes = &local_nbytes;

	value = 0;
	ndigits = 0;
	*nbytes = 0;
	negative = false;
	sign = false;

	/* Validate the specified base */
	if (base != 0 && !(base >= 2 && base <= 36))
		return (EINVAL);

	/* Skip any leading whitespace */
	for (; *nbytes < maxlen; (*nbytes)++) {
		if (!bhnd_nv_isspace(str[*nbytes]))
			break;
	}

	/* Empty string? */
	if (*nbytes == maxlen)
		return (EFTYPE);

	/* Parse and skip sign */
	if (str[*nbytes] == '-') {
		negative = true;
		sign = true;
		(*nbytes)++;
	} else if (str[*nbytes] == '+') {
		sign = true;
		(*nbytes)++;
	}

	/* Truncated after sign character? */
	if (*nbytes == maxlen)
		return (EFTYPE);

	/* Identify (or validate) hex base, skipping 0x/0X prefix */
	if (base == 16 || base == 0) {
		/* Check for (and skip) 0x/0X prefix */
		if (maxlen - *nbytes >= 2 && str[*nbytes] == '0' &&
		    (str[*nbytes+1] == 'x' || str[*nbytes+1] == 'X'))
		{
			base = 16;
			(*nbytes) += 2;
		}
	}

	/* Truncated after hex prefix? */
	if (*nbytes == maxlen)
		return (EFTYPE);

	/* Differentiate decimal/octal by looking for a leading 0 */
	if (base == 0) {
		if (str[*nbytes] == '0') {
			base = 8;
		} else {
			base = 10;
		}
	}

	/* Only enable twos-compliment signed integer parsing enabled if the
	 * input is base 16, and no explicit sign prefix was provided */
	if (!sign && base == 16)
		twos_compl = true;
	else
		twos_compl = false;

	/* Determine the maximum value representable by the requested type */
	switch (otype) {
	case BHND_NVRAM_TYPE_CHAR:
	case BHND_NVRAM_TYPE_UINT8:
		type_max = (uint64_t)UINT8_MAX;
		break;
	case BHND_NVRAM_TYPE_UINT16:
		type_max = (uint64_t)UINT16_MAX;
		break;
	case BHND_NVRAM_TYPE_UINT32:
		type_max = (uint64_t)UINT32_MAX;
		break;
	case BHND_NVRAM_TYPE_UINT64:
		type_max = (uint64_t)UINT64_MAX;
		break;

	case BHND_NVRAM_TYPE_INT8:
		if (twos_compl)
			type_max = (uint64_t)UINT8_MAX;
		else if (negative)
			type_max = -(uint64_t)INT8_MIN;
		else
			type_max = (uint64_t)INT8_MAX;
		break;

	case BHND_NVRAM_TYPE_INT16:
		if (twos_compl)
			type_max = (uint64_t)UINT16_MAX;
		else if (negative)
			type_max = -(uint64_t)INT16_MIN;
		else
			type_max = (uint64_t)INT16_MAX;
		break;

	case BHND_NVRAM_TYPE_INT32:
		if (twos_compl)
			type_max = (uint64_t)UINT32_MAX;
		else if (negative)
			type_max = -(uint64_t)INT32_MIN;
		else
			type_max = (uint64_t)INT32_MAX;
		break;

	case BHND_NVRAM_TYPE_INT64:
		if (twos_compl)
			type_max = (uint64_t)UINT64_MAX;
		else if (negative)
			type_max = -(uint64_t)INT64_MIN;
		else
			type_max = (uint64_t)INT64_MAX;
		break;

	default:
		BHND_NV_LOG("unsupported integer type: %d\n", otype);
		return (EINVAL);
	}

	/* The maximum value after which an additional carry would overflow */
	value_max = type_max / (uint64_t)base;

	/* The maximum carry value given a value equal to value_max */
	carry_max = type_max % (uint64_t)base;

	/* Consume input until we hit maxlen or a non-digit character */
	for (; *nbytes < maxlen; (*nbytes)++) {
		u_long	carry;
		char	c;

		/* Parse carry value */
		c = str[*nbytes];
		if (bhnd_nv_isdigit(c)) {
			carry = c - '0';
		} else if (bhnd_nv_isxdigit(c)) {
			if (bhnd_nv_isupper(c))
				carry = (c - 'A') + 10;
			else
				carry = (c - 'a') + 10;
		} else {
			/* Hit first non-digit character */
			break;
		}

		/* If carry is outside the base, it's not a valid digit
		 * in the current parse context; consider it a non-digit
		 * character */
		if (carry >= (uint64_t)base)
			break;

		/* Increment count of parsed digits */
		ndigits++;

		if (value > value_max) {
			/* -Any- carry value would overflow */
			return (ERANGE);
		} else if (value == value_max && carry > carry_max) {
			/* -This- carry value would overflow */
			return (ERANGE);
		}

		value *= (uint64_t)base;
		value += carry;
	}

	/* If we hit a non-digit character before parsing the first digit,
	 * we hit an empty integer string. */
	if (ndigits == 0)
		return (EFTYPE);

	if (negative)
		value = -value;

	/* Provide (and verify) required length */
	*olen = bhnd_nvram_type_width(otype);
	if (outp == NULL)
		return (0);
	else if (limit < *olen)
		return (ENOMEM);

	/* Provide result */
	switch (otype) {
	case BHND_NVRAM_TYPE_CHAR:
	case BHND_NVRAM_TYPE_UINT8:
		*(uint8_t *)outp = (uint8_t)value;
		break;
	case BHND_NVRAM_TYPE_UINT16:
		*(uint16_t *)outp = (uint16_t)value;
		break;
	case BHND_NVRAM_TYPE_UINT32:
		*(uint32_t *)outp = (uint32_t)value;
		break;
	case BHND_NVRAM_TYPE_UINT64:
		*(uint64_t *)outp = (uint64_t)value;
		break;

	case BHND_NVRAM_TYPE_INT8:
		*(int8_t *)outp = (int8_t)(int64_t)value;
		break;
	case BHND_NVRAM_TYPE_INT16:
		*(int16_t *)outp = (int16_t)(int64_t)value;
		break;
	case BHND_NVRAM_TYPE_INT32:
		*(int32_t *)outp = (int32_t)(int64_t)value;
		break;
	case BHND_NVRAM_TYPE_INT64:
		*(int64_t *)outp = (int64_t)value;
		break;
	default:
		/* unreachable */
		BHND_NV_PANIC("unhandled type %d\n", otype);
	}

	return (0);
}
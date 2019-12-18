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

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nv_isxdigit (char const) ; 
 char* memchr (char const*,char const,size_t) ; 

__attribute__((used)) static bool
bhnd_nvram_ident_octet_string(const char *inp, size_t ilen, char *delim,
    size_t *nelem)
{
	size_t	elem_count;
	size_t	max_elem_count, min_elem_count;
	size_t	field_count;
	char	idelim;

	field_count = 0;

	/* Require exactly two digits. If we relax this, there is room
	 * for ambiguity with signed integers and the '-' delimiter */
	min_elem_count = 2;
	max_elem_count = 2;

	/* Identify the delimiter used. The standard delimiter for MAC
	 * addresses is ':', but some earlier NVRAM formats may use '-' */
	for (const char *d = ":-";; d++) {
		const char *loc;

		/* No delimiter found, not an octet string */
		if (*d == '\0')
			return (false);

		/* Look for the delimiter */
		if ((loc = memchr(inp, *d, ilen)) == NULL)
			continue;

		/* Delimiter found */
		idelim = *loc;
		break;
	}

	/* To disambiguate from signed integers, if the delimiter is "-",
	 * the octets must be exactly 2 chars each */
	if (idelim == '-')
		min_elem_count = 2;

	/* String must be composed of individual octets (zero or more hex
	 * digits) separated by our delimiter. */
	elem_count = 0;
	for (const char *p = inp; (size_t)(p - inp) < ilen; p++) {
		switch (*p) {
		case ':':
		case '-':
		case '\0':
			/* Hit a delim character; all delims must match
			 * the first delimiter used */
			if (*p != '\0' && *p != idelim)
				return (false);

			/* Must have parsed at least min_elem_count digits */
			if (elem_count < min_elem_count)
				return (false);

			/* Reset element count */
			elem_count = 0;

			/* Bump field count */
			field_count++;
			break;
		default:
			/* More than maximum number of hex digits? */
			if (elem_count >= max_elem_count)
				return (false);

			/* Octet values must be hex digits */
			if (!bhnd_nv_isxdigit(*p))
				return (false);

			elem_count++;
			break;
		}
	}

	if (delim != NULL)
		*delim = idelim;

	if (nelem != NULL)
		*nelem = field_count;

	return (true);
}
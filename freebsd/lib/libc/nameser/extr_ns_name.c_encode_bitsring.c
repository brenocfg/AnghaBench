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
 unsigned char DNS_LABELTYPE_BITSTRING ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int* digitvalue ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static int
encode_bitsring(const char **bp, const char *end, unsigned char **labelp,
		unsigned char ** dst, unsigned const char *eom)
{
	int afterslash = 0;
	const char *cp = *bp;
	unsigned char *tp;
	char c;
	const char *beg_blen;
	char *end_blen = NULL;
	int value = 0, count = 0, tbcount = 0, blen = 0;

	beg_blen = end_blen = NULL;

	/* a bitstring must contain at least 2 characters */
	if (end - cp < 2)
		return (EINVAL);

	/* XXX: currently, only hex strings are supported */
	if (*cp++ != 'x')
		return (EINVAL);
	if (!isxdigit((*cp) & 0xff)) /*%< reject '\[x/BLEN]' */
		return (EINVAL);

	for (tp = *dst + 1; cp < end && tp < eom; cp++) {
		switch((c = *cp)) {
		case ']':	/*%< end of the bitstring */
			if (afterslash) {
				if (beg_blen == NULL)
					return (EINVAL);
				blen = (int)strtol(beg_blen, &end_blen, 10);
				if (*end_blen != ']')
					return (EINVAL);
			}
			if (count)
				*tp++ = ((value << 4) & 0xff);
			cp++;	/*%< skip ']' */
			goto done;
		case '/':
			afterslash = 1;
			break;
		default:
			if (afterslash) {
				if (!isdigit(c&0xff))
					return (EINVAL);
				if (beg_blen == NULL) {
					
					if (c == '0') {
						/* blen never begings with 0 */
						return (EINVAL);
					}
					beg_blen = cp;
				}
			} else {
				if (!isxdigit(c&0xff))
					return (EINVAL);
				value <<= 4;
				value += digitvalue[(int)c];
				count += 4;
				tbcount += 4;
				if (tbcount > 256)
					return (EINVAL);
				if (count == 8) {
					*tp++ = value;
					count = 0;
				}
			}
			break;
		}
	}
  done:
	if (cp >= end || tp >= eom)
		return (EMSGSIZE);

	/*
	 * bit length validation:
	 * If a <length> is present, the number of digits in the <bit-data>
	 * MUST be just sufficient to contain the number of bits specified
	 * by the <length>. If there are insignificant bits in a final
	 * hexadecimal or octal digit, they MUST be zero.
	 * RFC2673, Section 3.2.
	 */
	if (blen > 0) {
		int traillen;

		if (((blen + 3) & ~3) != tbcount)
			return (EINVAL);
		traillen = tbcount - blen; /*%< between 0 and 3 */
		if (((value << (8 - traillen)) & 0xff) != 0)
			return (EINVAL);
	}
	else
		blen = tbcount;
	if (blen == 256)
		blen = 0;

	/* encode the type and the significant bit fields */
	**labelp = DNS_LABELTYPE_BITSTRING;
	**dst = blen;

	*bp = cp;
	*dst = tp;

	return (0);
}
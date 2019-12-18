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
typedef  int u_int ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NS_INADDRSZ ; 
 int htonl (int) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int /*<<< orphan*/ ) ; 

int
strtoaddr(const char *src, void *dst)
{
	uint32_t val;
	u_int digit;
	ptrdiff_t n;
	unsigned char c;
	u_int parts[4];
	u_int *pp = parts;

	c = *src;
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, isdigit=decimal.
		 */
		if (!isdigit(c))
			return (0);
		val = 0;
		if (c == '0') {
			c = *++src;
			if (c == 'x' || c == 'X')
				return (0);
			else if (isdigit(c) && c != '9')
				return (0);
		}
		for (;;) {
			if (isdigit(c)) {
				digit = c - '0';
				if (digit >= 10)
					break;
				val = (val * 10) + digit;
				c = *++src;
			} else
				break;
		}
		if (c == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16 bits)
			 *	a.b	(with b treated as 24 bits)
			 *	a	(with a treated as 32 bits)
			 */
			if (pp >= parts + 3)
				return (0);
			*pp++ = val;
			c = *++src;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && !isspace(c))
		return (0);
	/*
	 * Find the number of parts specified.
	 * It must be 4; we only support dotted quads, we don't
	 * support shorthand.
	 */
	n = pp - parts + 1;
	if (n != 4)
		return (0);
	/*
	 * parts[0-2] were set to the first 3 parts of the address;
	 * val was set to the 4th part.
	 *
	 * Check if any part is bigger than 255.
	 */
	if ((parts[0] | parts[1] | parts[2] | val) > 0xff)
		return (0);
	/*
	 * Add the other three parts to val.
	 */
	val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
	if (dst) {
		val = htonl(val);
		memcpy(dst, &val, NS_INADDRSZ);
	}
	return (1);
}
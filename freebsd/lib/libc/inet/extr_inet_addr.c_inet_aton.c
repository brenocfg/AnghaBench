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
typedef  int u_long ;
typedef  int u_int8_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ isascii (char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 scalar_t__ isxdigit (unsigned char) ; 

int
inet_aton(const char *cp, struct in_addr *addr) {
	u_long val;
	int base, n;
	char c;
	u_int8_t parts[4];
	u_int8_t *pp = parts;
	int digit;

	c = *cp;
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, isdigit=decimal.
		 */
		if (!isdigit((unsigned char)c))
			return (0);
		val = 0; base = 10; digit = 0;
		if (c == '0') {
			c = *++cp;
			if (c == 'x' || c == 'X')
				base = 16, c = *++cp;
			else {
				base = 8;
				digit = 1 ;
			}
		}
		for (;;) {
			if (isascii(c) && isdigit((unsigned char)c)) {
				if (base == 8 && (c == '8' || c == '9'))
					return (0);
				val = (val * base) + (c - '0');
				c = *++cp;
				digit = 1;
			} else if (base == 16 && isascii(c) && 
				   isxdigit((unsigned char)c)) {
				val = (val << 4) |
					(c + 10 - (islower((unsigned char)c) ? 'a' : 'A'));
				c = *++cp;
				digit = 1;
			} else
				break;
		}
		if (c == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16 bits)
			 *	a.b	(with b treated as 24 bits)
			 */
			if (pp >= parts + 3 || val > 0xffU)
				return (0);
			*pp++ = val;
			c = *++cp;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && (!isascii(c) || !isspace((unsigned char)c)))
		return (0);
	/*
	 * Did we get a valid digit?
	 */
	if (!digit)
		return (0);
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
	n = pp - parts + 1;
	switch (n) {
	case 1:				/*%< a -- 32 bits */
		break;

	case 2:				/*%< a.b -- 8.24 bits */
		if (val > 0xffffffU)
			return (0);
		val |= (uint32_t)parts[0] << 24;
		break;

	case 3:				/*%< a.b.c -- 8.8.16 bits */
		if (val > 0xffffU)
			return (0);
		val |= ((uint32_t)parts[0] << 24) | (parts[1] << 16);
		break;

	case 4:				/*%< a.b.c.d -- 8.8.8.8 bits */
		if (val > 0xffU)
			return (0);
		val |= ((uint32_t)parts[0] << 24) | (parts[1] << 16) |
		    (parts[2] << 8);
		break;
	}
	if (addr != NULL)
		addr->s_addr = htonl(val);
	return (1);
}
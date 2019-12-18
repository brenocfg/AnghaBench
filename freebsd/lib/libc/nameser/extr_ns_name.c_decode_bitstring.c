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
 int SPRINTF (char*) ; 

__attribute__((used)) static int
decode_bitstring(const unsigned char **cpp, char *dn, const char *eom)
{
	const unsigned char *cp = *cpp;
	char *beg = dn, tc;
	int b, blen, plen, i;

	if ((blen = (*cp & 0xff)) == 0)
		blen = 256;
	plen = (blen + 3) / 4;
	plen += sizeof("\\[x/]") + (blen > 99 ? 3 : (blen > 9) ? 2 : 1);
	if (dn + plen >= eom)
		return (-1);

	cp++;
	i = SPRINTF((dn, "\\[x"));
	if (i < 0)
		return (-1);
	dn += i;
	for (b = blen; b > 7; b -= 8, cp++) {
		i = SPRINTF((dn, "%02x", *cp & 0xff));
		if (i < 0)
			return (-1);
		dn += i;
	}
	if (b > 4) {
		tc = *cp++;
		i = SPRINTF((dn, "%02x", tc & (0xff << (8 - b))));
		if (i < 0)
			return (-1);
		dn += i;
	} else if (b > 0) {
		tc = *cp++;
		i = SPRINTF((dn, "%1x",
			       ((tc >> 4) & 0x0f) & (0x0f << (4 - b)))); 
		if (i < 0)
			return (-1);
		dn += i;
	}
	i = SPRINTF((dn, "/%d]", blen));
	if (i < 0)
		return (-1);
	dn += i;

	*cpp = cp;
	return (dn - beg);
}
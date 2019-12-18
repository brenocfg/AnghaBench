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
typedef  int uint8_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int const FR_EA_BIT ; 
 int /*<<< orphan*/  ND_TTEST (int const) ; 

__attribute__((used)) static int parse_q922_addr(netdissect_options *ndo,
                           const u_char *p, u_int *dlci,
                           u_int *addr_len, uint8_t *flags, u_int length)
{
	if (!ND_TTEST(p[0]) || length < 1)
		return -1;
	if ((p[0] & FR_EA_BIT))
		return 0;

	if (!ND_TTEST(p[1]) || length < 2)
		return -1;
	*addr_len = 2;
	*dlci = ((p[0] & 0xFC) << 2) | ((p[1] & 0xF0) >> 4);

        flags[0] = p[0] & 0x02; /* populate the first flag fields */
        flags[1] = p[1] & 0x0c;
        flags[2] = 0;           /* clear the rest of the flags */
        flags[3] = 0;

	if (p[1] & FR_EA_BIT)
		return 1;	/* 2-byte Q.922 address */

	p += 2;
	length -= 2;
	if (!ND_TTEST(p[0]) || length < 1)
		return -1;
	(*addr_len)++;		/* 3- or 4-byte Q.922 address */
	if ((p[0] & FR_EA_BIT) == 0) {
		*dlci = (*dlci << 7) | (p[0] >> 1);
		(*addr_len)++;	/* 4-byte Q.922 address */
		p++;
		length--;
	}

	if (!ND_TTEST(p[0]) || length < 1)
		return -1;
	if ((p[0] & FR_EA_BIT) == 0)
		return 0; /* more than 4 bytes of Q.922 address? */

        flags[3] = p[0] & 0x02;

        *dlci = (*dlci << 6) | (p[0] >> 2);

	return 1;
}
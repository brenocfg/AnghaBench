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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */

int
uni_nsap2e164(char *e164, const u_char *nsap, int check)
{
	char *p = e164;
	u_int d;
	int i;

	if(nsap[0] != 0x45)
		return -1;
	if((nsap[8] & 0xf) != 0xf)
		return -1;
	for(i = 1; i <= 7; i++) {
		d = (nsap[i] >> 4) & 0xf;
		if(d == 0x00 && p == e164)
			continue;
		if(d >= 0xa)
			return -1;
		*p++ = d + '0';

		d = nsap[i] & 0xf;
		if(d == 0x00 && p == e164)
			continue;
		if(d >= 0xa)
			return -1;
		*p++ = d + '0';
	}
	d = (nsap[i] >> 4) & 0xf;
	if(d != 0x00 || p == e164) {
		if(d >= 0xa)
			return -1;
		*p++ = d + '0';
	}
	if(p == e164)
		return -1;
	*p++ = 0;

	if(check == 0)
		return 0;
	while(i < ((check == 1) ? 19 : 20)) {
		if(nsap[i] != 0x00)
			return -1;
		i++;
	}

	return 0;
}
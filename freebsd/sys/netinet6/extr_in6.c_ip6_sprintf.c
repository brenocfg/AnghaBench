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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
typedef  int u_char ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 void** digits ; 

char *
ip6_sprintf(char *ip6buf, const struct in6_addr *addr)
{
	int i, cnt = 0, maxcnt = 0, idx = 0, index = 0;
	char *cp;
	const u_int16_t *a = (const u_int16_t *)addr;
	const u_int8_t *d;
	int dcolon = 0, zero = 0;

	cp = ip6buf;

	for (i = 0; i < 8; i++) {
		if (*(a + i) == 0) {
			cnt++;
			if (cnt == 1)
				idx = i;
		}
		else if (maxcnt < cnt) {
			maxcnt = cnt;
			index = idx;
			cnt = 0;
		}
	}
	if (maxcnt < cnt) {
		maxcnt = cnt;
		index = idx;
	}

	for (i = 0; i < 8; i++) {
		if (dcolon == 1) {
			if (*a == 0) {
				if (i == 7)
					*cp++ = ':';
				a++;
				continue;
			} else
				dcolon = 2;
		}
		if (*a == 0) {
			if (dcolon == 0 && *(a + 1) == 0 && i == index) {
				if (i == 0)
					*cp++ = ':';
				*cp++ = ':';
				dcolon = 1;
			} else {
				*cp++ = '0';
				*cp++ = ':';
			}
			a++;
			continue;
		}
		d = (const u_char *)a;
		/* Try to eliminate leading zeros in printout like in :0001. */
		zero = 1;
		*cp = digits[*d >> 4];
		if (*cp != '0') {
			zero = 0;
			cp++;
		}
		*cp = digits[*d++ & 0xf];
		if (zero == 0 || (*cp != '0')) {
			zero = 0;
			cp++;
		}
		*cp = digits[*d >> 4];
		if (zero == 0 || (*cp != '0')) {
			zero = 0;
			cp++;
		}
		*cp++ = digits[*d & 0xf];
		*cp++ = ':';
		a++;
	}
	*--cp = '\0';
	return (ip6buf);
}
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
typedef  int u_char ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKLEN (int,int) ; 

__attribute__((used)) static int
mask2len(const struct in6_addr *addr, int lenlim)
{
	int i = 0, j;
	const u_char *p = (const u_char *)addr;

	for (j = 0; j < lenlim; j++, p++) {
		if (*p != 0xff)
			break;
		i += 8;
	}
	if (j < lenlim) {
		switch (*p) {
#define	MASKLEN(m, l)	case m: do { i += l; break; } while (0)
		MASKLEN(0xfe, 7); break;
		MASKLEN(0xfc, 6); break;
		MASKLEN(0xf8, 5); break;
		MASKLEN(0xf0, 4); break;
		MASKLEN(0xe0, 3); break;
		MASKLEN(0xc0, 2); break;
		MASKLEN(0x80, 1); break;
#undef	MASKLEN
		}
	}
	return i;
}
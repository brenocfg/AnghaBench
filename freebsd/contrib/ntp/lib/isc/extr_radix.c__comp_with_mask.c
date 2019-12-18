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
 scalar_t__ memcmp (void*,void*,int) ; 

__attribute__((used)) static int
_comp_with_mask(void *addr, void *dest, u_int mask) {

	/* Mask length of zero matches everything */
	if (mask == 0)
		return (1);

	if (memcmp(addr, dest, mask / 8) == 0) {
		int n = mask / 8;
		int m = ((~0) << (8 - (mask % 8)));

		if ((mask % 8) == 0 ||
		    (((u_char *)addr)[n] & m) == (((u_char *)dest)[n] & m))
			return (1);
	}
	return (0);
}
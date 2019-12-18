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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int fls (scalar_t__) ; 

__attribute__((used)) static u_int
isqrt(u_int num)
{
	u_int bit, root, tmp;

	bit = num != 0 ? (1u << ((fls(num) - 1) & ~1)) : 0;
	root = 0;
	while (bit != 0) {
		tmp = root + bit;
		root >>= 1;
		if (num >= tmp) {
			num -= tmp;
			root += bit;
		}
		bit >>= 2;
	}
	return (root);
}
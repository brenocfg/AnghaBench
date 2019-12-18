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
typedef  unsigned long u64 ;

/* Variables and functions */

__attribute__((used)) static inline void
copy_reg(const u64 *fr, u64 fnat, unsigned long *tr, unsigned long *tnat)
{
	u64 fslot, tslot, nat;
	*tr = *fr;
	fslot = ((unsigned long)fr >> 3) & 63;
	tslot = ((unsigned long)tr >> 3) & 63;
	*tnat &= ~(1UL << tslot);
	nat = (fnat >> fslot) & 1;
	*tnat |= (nat << tslot);
}
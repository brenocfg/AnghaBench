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
typedef  int s64 ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 unsigned long MIPS_ENTRYLO_RI ; 
 unsigned long MIPS_ENTRYLO_XI ; 

__attribute__((used)) static inline unsigned long entrylo_user_to_kvm(s64 v)
{
	unsigned long mask, ret = v;

	if (BITS_PER_LONG == 32) {
		/*
		 * KVM API exposes 64-bit versiono of the register, so move the
		 * RI/XI bits down into place.
		 */
		mask = MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI;
		ret &= ~mask;
		ret |= (v >> 32) & mask;
	}
	return ret;
}
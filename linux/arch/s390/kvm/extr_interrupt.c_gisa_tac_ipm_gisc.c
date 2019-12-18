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
typedef  scalar_t__ u32 ;
struct kvm_s390_gisa {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPM_BIT_OFFSET ; 
 int test_and_clear_bit_inv (scalar_t__,unsigned long*) ; 

__attribute__((used)) static inline int gisa_tac_ipm_gisc(struct kvm_s390_gisa *gisa, u32 gisc)
{
	return test_and_clear_bit_inv(IPM_BIT_OFFSET + gisc, (unsigned long *) gisa);
}
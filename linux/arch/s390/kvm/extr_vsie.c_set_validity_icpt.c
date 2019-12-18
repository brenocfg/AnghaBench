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
struct kvm_s390_sie_block {int ipa; int ipb; int /*<<< orphan*/  icptcode; } ;
typedef  int __u32 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ICPT_VALIDITY ; 

__attribute__((used)) static int set_validity_icpt(struct kvm_s390_sie_block *scb,
			     __u16 reason_code)
{
	scb->ipa = 0x1000;
	scb->ipb = ((__u32) reason_code) << 16;
	scb->icptcode = ICPT_VALIDITY;
	return 1;
}
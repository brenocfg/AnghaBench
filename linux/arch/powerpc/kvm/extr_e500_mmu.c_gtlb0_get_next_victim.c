#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_vcpu_e500 {scalar_t__* gtlb_nv; TYPE_1__* gtlb_params; } ;
struct TYPE_2__ {scalar_t__ ways; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned int gtlb0_get_next_victim(
		struct kvmppc_vcpu_e500 *vcpu_e500)
{
	unsigned int victim;

	victim = vcpu_e500->gtlb_nv[0]++;
	if (unlikely(vcpu_e500->gtlb_nv[0] >= vcpu_e500->gtlb_params[0].ways))
		vcpu_e500->gtlb_nv[0] = 0;

	return victim;
}
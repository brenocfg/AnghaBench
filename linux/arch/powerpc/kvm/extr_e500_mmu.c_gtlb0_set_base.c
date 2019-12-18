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
struct kvmppc_vcpu_e500 {TYPE_1__* gtlb_params; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_2__ {int /*<<< orphan*/  ways; int /*<<< orphan*/  sets; } ;

/* Variables and functions */
 int tlb0_set_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtlb0_set_base(struct kvmppc_vcpu_e500 *vcpu_e500, gva_t addr)
{
	return tlb0_set_base(addr, vcpu_e500->gtlb_params[0].sets,
			     vcpu_e500->gtlb_params[0].ways);
}
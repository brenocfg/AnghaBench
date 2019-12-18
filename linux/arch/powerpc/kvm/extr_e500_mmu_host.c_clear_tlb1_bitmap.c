#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kvmppc_vcpu_e500 {scalar_t__ h2g_tlb1_rmap; TYPE_1__* gtlb_params; scalar_t__ g2h_tlb1_map; } ;
struct TYPE_4__ {int entries; } ;
struct TYPE_3__ {int entries; } ;

/* Variables and functions */
 TYPE_2__* host_tlb_params ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_tlb1_bitmap(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	if (vcpu_e500->g2h_tlb1_map)
		memset(vcpu_e500->g2h_tlb1_map, 0,
		       sizeof(u64) * vcpu_e500->gtlb_params[1].entries);
	if (vcpu_e500->h2g_tlb1_rmap)
		memset(vcpu_e500->h2g_tlb1_rmap, 0,
		       sizeof(unsigned int) * host_tlb_params[1].entries);
}
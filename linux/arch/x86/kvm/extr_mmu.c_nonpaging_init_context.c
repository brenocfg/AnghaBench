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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int direct_map; int nx; int /*<<< orphan*/  shadow_root_level; scalar_t__ root_level; int /*<<< orphan*/  update_pte; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT32E_ROOT_LEVEL ; 
 int /*<<< orphan*/  nonpaging_gva_to_gpa ; 
 int /*<<< orphan*/  nonpaging_invlpg ; 
 int /*<<< orphan*/  nonpaging_page_fault ; 
 int /*<<< orphan*/  nonpaging_sync_page ; 
 int /*<<< orphan*/  nonpaging_update_pte ; 

__attribute__((used)) static void nonpaging_init_context(struct kvm_vcpu *vcpu,
				   struct kvm_mmu *context)
{
	context->page_fault = nonpaging_page_fault;
	context->gva_to_gpa = nonpaging_gva_to_gpa;
	context->sync_page = nonpaging_sync_page;
	context->invlpg = nonpaging_invlpg;
	context->update_pte = nonpaging_update_pte;
	context->root_level = 0;
	context->shadow_root_level = PT32E_ROOT_LEVEL;
	context->direct_map = true;
	context->nx = false;
}
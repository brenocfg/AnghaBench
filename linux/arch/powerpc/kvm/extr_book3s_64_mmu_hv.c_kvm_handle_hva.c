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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  hva_handler_fn ;

/* Variables and functions */
 int kvm_handle_hva_range (struct kvm*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_handle_hva(struct kvm *kvm, unsigned long hva,
			  hva_handler_fn handler)
{
	return kvm_handle_hva_range(kvm, hva, hva + 1, handler);
}
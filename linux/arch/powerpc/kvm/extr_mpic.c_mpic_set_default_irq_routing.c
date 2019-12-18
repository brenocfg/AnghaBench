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
struct openpic {int /*<<< orphan*/  kvm; } ;
struct kvm_irq_routing_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct kvm_irq_routing_entry*) ; 
 int /*<<< orphan*/  kvm_set_irq_routing (int /*<<< orphan*/ ,struct kvm_irq_routing_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_irq_routing_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpic_set_default_irq_routing(struct openpic *opp)
{
	struct kvm_irq_routing_entry *routing;

	/* Create a nop default map, so that dereferencing it still works */
	routing = kzalloc((sizeof(*routing)), GFP_KERNEL);
	if (!routing)
		return -ENOMEM;

	kvm_set_irq_routing(opp->kvm, routing, 0, 0);

	kfree(routing);
	return 0;
}
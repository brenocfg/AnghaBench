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
typedef  int /*<<< orphan*/  u32 ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int __x86_set_memory_region (struct kvm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int x86_set_memory_region(struct kvm *kvm, int id, gpa_t gpa, u32 size)
{
	int r;

	mutex_lock(&kvm->slots_lock);
	r = __x86_set_memory_region(kvm, id, gpa, size);
	mutex_unlock(&kvm->slots_lock);

	return r;
}
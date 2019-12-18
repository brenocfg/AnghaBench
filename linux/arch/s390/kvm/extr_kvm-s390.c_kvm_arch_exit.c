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

/* Variables and functions */
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_dbf ; 
 int /*<<< orphan*/  kvm_s390_gib_destroy () ; 

void kvm_arch_exit(void)
{
	kvm_s390_gib_destroy();
	debug_unregister(kvm_s390_dbf);
}
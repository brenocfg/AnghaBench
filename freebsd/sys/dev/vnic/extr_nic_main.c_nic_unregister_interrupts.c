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
struct nicpf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nic_disable_msix (struct nicpf*) ; 
 int /*<<< orphan*/  nic_free_all_interrupts (struct nicpf*) ; 

__attribute__((used)) static void
nic_unregister_interrupts(struct nicpf *nic)
{

	nic_free_all_interrupts(nic);
	nic_disable_msix(nic);
}
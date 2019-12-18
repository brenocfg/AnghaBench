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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 TYPE_1__ qp_guest_endpoints ; 
 int /*<<< orphan*/  vmci_mutex_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_mutex_release (int /*<<< orphan*/ *) ; 

void
vmci_qp_guest_endpoints_sync(void)
{

	vmci_mutex_acquire(&qp_guest_endpoints.mutex);
	vmci_mutex_release(&qp_guest_endpoints.mutex);
}
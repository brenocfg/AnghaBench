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
 int /*<<< orphan*/  qp_guest_endpoints ; 
 int queue_pair_list_init (int /*<<< orphan*/ *) ; 

int
vmci_qp_guest_endpoints_init(void)
{

	return (queue_pair_list_init(&qp_guest_endpoints));
}
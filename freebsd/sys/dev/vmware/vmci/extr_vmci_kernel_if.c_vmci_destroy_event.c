#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sema_mtx; } ;
typedef  TYPE_1__ vmci_event ;

/* Variables and functions */
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_destroy (TYPE_1__*) ; 

void
vmci_destroy_event(vmci_event *event)
{

	if (mtx_owned(&event->sema_mtx))
		sema_destroy(event);
}
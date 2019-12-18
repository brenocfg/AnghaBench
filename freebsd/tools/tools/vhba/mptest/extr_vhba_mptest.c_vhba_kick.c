#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* private; } ;
typedef  TYPE_1__ vhba_softc_t ;
struct TYPE_5__ {int /*<<< orphan*/  qt; } ;
typedef  TYPE_2__ mptest_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

void
vhba_kick(vhba_softc_t *vhba)
{
	mptest_t *vhbas = vhba->private;
	taskqueue_enqueue(taskqueue_swi, &vhbas->qt);
}
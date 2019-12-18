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
struct TYPE_5__ {int /*<<< orphan*/  disk; int /*<<< orphan*/  tick; } ;
typedef  TYPE_2__ mptest_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vhba_fini(vhba_softc_t *vhba)
{
	mptest_t *vhbas = vhba->private;
	callout_stop(&vhbas->tick);
	vhba->private = NULL;
	free(vhbas->disk, M_DEVBUF);
}
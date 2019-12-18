#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* private; } ;
typedef  TYPE_1__ vhba_softc_t ;
struct TYPE_7__ {int disk_size; int* luns; int /*<<< orphan*/  qt; int /*<<< orphan*/  inproc; int /*<<< orphan*/  tick; int /*<<< orphan*/  disk; TYPE_1__* vhba; } ;
typedef  TYPE_2__ mptest_t ;

/* Variables and functions */
 int DISK_SIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  VMP_TIME ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vhba_task ; 
 int /*<<< orphan*/  vhba_timer ; 

void
vhba_init(vhba_softc_t *vhba)
{
	static mptest_t vhbastatic;

	vhbastatic.vhba = vhba;
	vhbastatic.disk_size = DISK_SIZE << 20;
	vhbastatic.disk = malloc(vhbastatic.disk_size, M_DEVBUF, M_WAITOK|M_ZERO);
	vhba->private = &vhbastatic;
	callout_init_mtx(&vhbastatic.tick, &vhba->lock, 0);
	callout_reset(&vhbastatic.tick, VMP_TIME, vhba_timer, vhba);
	TAILQ_INIT(&vhbastatic.inproc);
	TASK_INIT(&vhbastatic.qt, 0, vhba_task, &vhbastatic);
	vhbastatic.luns[0] = 1;
	vhbastatic.luns[1] = 1;
}
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
struct ctl_softc {int /*<<< orphan*/  pending_lun_queue; int /*<<< orphan*/  ctl_lock; } ;
struct ctl_be_lun {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ctl_be_lun*,int /*<<< orphan*/ ) ; 
 struct ctl_softc* control_softc ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
ctl_add_lun(struct ctl_be_lun *be_lun)
{
	struct ctl_softc *softc = control_softc;

	mtx_lock(&softc->ctl_lock);
	STAILQ_INSERT_TAIL(&softc->pending_lun_queue, be_lun, links);
	mtx_unlock(&softc->ctl_lock);
	wakeup(&softc->pending_lun_queue);

	return (0);
}
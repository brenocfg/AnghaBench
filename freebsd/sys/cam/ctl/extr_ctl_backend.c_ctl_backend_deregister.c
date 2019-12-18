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
struct ctl_softc {int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/  num_backends; int /*<<< orphan*/  be_list; } ;
struct ctl_backend_driver {int (* shutdown ) () ;char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_backend_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ctl_softc* control_softc ; 
 int /*<<< orphan*/  ctl_backend_driver ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int stub1 () ; 

int
ctl_backend_deregister(struct ctl_backend_driver *be)
{
	struct ctl_softc *softc = control_softc;
	int error;

	/* Call the backend's shutdown routine. */
	if (be->shutdown != NULL) {
		if ((error = be->shutdown()) != 0) {
			printf("%s backend shutdown error: %d\n",
			    be->name, error);
			return (error);
		}
	}

	mtx_lock(&softc->ctl_lock);
	STAILQ_REMOVE(&softc->be_list, be, ctl_backend_driver, links);
	softc->num_backends--;
	mtx_unlock(&softc->ctl_lock);
	return (0);
}
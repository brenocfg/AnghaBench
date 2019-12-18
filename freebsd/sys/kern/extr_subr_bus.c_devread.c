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
struct uio {int dummy; } ;
struct dev_event_info {struct dev_event_info* dei_data; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  queued; int /*<<< orphan*/  devq; int /*<<< orphan*/  cv; scalar_t__ nonblock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  M_BUS ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct dev_event_info* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct dev_event_info*,int /*<<< orphan*/ ) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dei_link ; 
 TYPE_1__ devsoftc ; 
 int /*<<< orphan*/  free (struct dev_event_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (struct dev_event_info*) ; 
 int uiomove (struct dev_event_info*,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
devread(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct dev_event_info *n1;
	int rv;

	mtx_lock(&devsoftc.mtx);
	while (TAILQ_EMPTY(&devsoftc.devq)) {
		if (devsoftc.nonblock) {
			mtx_unlock(&devsoftc.mtx);
			return (EAGAIN);
		}
		rv = cv_wait_sig(&devsoftc.cv, &devsoftc.mtx);
		if (rv) {
			/*
			 * Need to translate ERESTART to EINTR here? -- jake
			 */
			mtx_unlock(&devsoftc.mtx);
			return (rv);
		}
	}
	n1 = TAILQ_FIRST(&devsoftc.devq);
	TAILQ_REMOVE(&devsoftc.devq, n1, dei_link);
	devsoftc.queued--;
	mtx_unlock(&devsoftc.mtx);
	rv = uiomove(n1->dei_data, strlen(n1->dei_data), uio);
	free(n1->dei_data, M_BUS);
	free(n1, M_BUS);
	return (rv);
}
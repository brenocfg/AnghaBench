#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct cuse_server {int /*<<< orphan*/  refs; TYPE_1__ selinfo; int /*<<< orphan*/  cv; int /*<<< orphan*/  hmem; int /*<<< orphan*/  hcli; int /*<<< orphan*/  hdev; int /*<<< orphan*/  head; int /*<<< orphan*/  pid; } ;
struct cdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_CUSE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuse_server*,int /*<<< orphan*/ ) ; 
 TYPE_2__* curproc ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_mtx ; 
 int /*<<< orphan*/  cuse_server_free ; 
 int /*<<< orphan*/  cuse_server_head ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devfs_set_cdevpriv (struct cuse_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct cuse_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cuse_server* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
cuse_server_open(struct cdev *dev, int fflags, int devtype, struct thread *td)
{
	struct cuse_server *pcs;

	pcs = malloc(sizeof(*pcs), M_CUSE, M_WAITOK | M_ZERO);
	if (pcs == NULL)
		return (ENOMEM);

	if (devfs_set_cdevpriv(pcs, &cuse_server_free)) {
		printf("Cuse: Cannot set cdevpriv.\n");
		free(pcs, M_CUSE);
		return (ENOMEM);
	}
	/* store current process ID */
	pcs->pid = curproc->p_pid;

	TAILQ_INIT(&pcs->head);
	TAILQ_INIT(&pcs->hdev);
	TAILQ_INIT(&pcs->hcli);
	TAILQ_INIT(&pcs->hmem);

	cv_init(&pcs->cv, "cuse-server-cv");

	knlist_init_mtx(&pcs->selinfo.si_note, &cuse_mtx);

	cuse_lock();
	pcs->refs++;
	TAILQ_INSERT_TAIL(&cuse_server_head, pcs, entry);
	cuse_unlock();

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct cuse_command {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tqe_prev; } ;
struct cuse_server_dev {int error; int got_signal; struct cuse_dev* user_dev; TYPE_4__* kern_dev; struct cuse_server* server; struct cuse_client* client; int /*<<< orphan*/  cv; int /*<<< orphan*/  command; int /*<<< orphan*/ * entered; struct cuse_command sub; TYPE_1__ entry; } ;
struct cuse_server {int /*<<< orphan*/  hdev; int /*<<< orphan*/  head; int /*<<< orphan*/  is_closing; int /*<<< orphan*/  cv; } ;
struct cuse_dev {int dummy; } ;
struct cuse_data_chunk {int /*<<< orphan*/  peer_ptr; } ;
struct cuse_create_dev {int permissions; int /*<<< orphan*/ * devname; int /*<<< orphan*/  group_id; int /*<<< orphan*/  user_id; struct cuse_dev* dev; } ;
struct cuse_client_command {int error; int got_signal; struct cuse_dev* user_dev; TYPE_4__* kern_dev; struct cuse_server* server; struct cuse_client* client; int /*<<< orphan*/  cv; int /*<<< orphan*/  command; int /*<<< orphan*/ * entered; struct cuse_command sub; TYPE_1__ entry; } ;
struct cuse_client {TYPE_3__* cmds; } ;
struct cuse_alloc_info {int /*<<< orphan*/  alloc_nr; int /*<<< orphan*/  page_count; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_8__ {struct cuse_server_dev* si_drv1; } ;
struct TYPE_6__ {uintptr_t per_file_handle; } ;
struct TYPE_7__ {TYPE_2__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUSE_ALLOC_PAGES_MAX ; 
 int /*<<< orphan*/  CUSE_ALLOC_UNIT_MAX ; 
 int /*<<< orphan*/  CUSE_BUF_MAX_PTR ; 
 int /*<<< orphan*/  CUSE_BUF_MIN_PTR ; 
 int CUSE_CMD_MAX ; 
 int /*<<< orphan*/  CUSE_CMD_SYNC ; 
 int CUSE_ID_DEFAULT (int) ; 
 int CUSE_ID_MASK ; 
#define  CUSE_IOCTL_ALLOC_MEMORY 142 
#define  CUSE_IOCTL_ALLOC_UNIT 141 
#define  CUSE_IOCTL_ALLOC_UNIT_BY_ID 140 
#define  CUSE_IOCTL_CREATE_DEV 139 
#define  CUSE_IOCTL_DESTROY_DEV 138 
#define  CUSE_IOCTL_FREE_MEMORY 137 
#define  CUSE_IOCTL_FREE_UNIT 136 
#define  CUSE_IOCTL_FREE_UNIT_BY_ID 135 
#define  CUSE_IOCTL_GET_COMMAND 134 
#define  CUSE_IOCTL_GET_SIG 133 
#define  CUSE_IOCTL_READ_DATA 132 
#define  CUSE_IOCTL_SELWAKEUP 131 
#define  CUSE_IOCTL_SET_PFH 130 
#define  CUSE_IOCTL_SYNC_COMMAND 129 
#define  CUSE_IOCTL_WRITE_DATA 128 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MAKEDEV_CHECKNAME ; 
 int /*<<< orphan*/  M_CUSE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
 struct cuse_server_dev* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 struct cuse_server_dev* TAILQ_NEXT (struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curthread ; 
 int cuse_alloc_unit_by_id_locked (struct cuse_server*,int) ; 
 int /*<<< orphan*/  cuse_client_devsw ; 
 int cuse_free_unit_by_id_locked (struct cuse_server*,int) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_mtx ; 
 int cuse_server_alloc_memory (struct cuse_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cuse_server_data_copy_locked (struct cuse_server_dev*,struct cuse_data_chunk*,int) ; 
 struct cuse_server_dev* cuse_server_find_command (struct cuse_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuse_server_free_dev (struct cuse_server_dev*) ; 
 int cuse_server_free_memory (struct cuse_server*,int /*<<< orphan*/ ) ; 
 int cuse_server_get (struct cuse_server**) ; 
 int cuse_server_ioctl_copy_locked (struct cuse_server_dev*,struct cuse_data_chunk*,int) ; 
 int /*<<< orphan*/  cuse_server_wakeup_all_client_locked (struct cuse_server*) ; 
 int /*<<< orphan*/  cuse_str_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 TYPE_4__* make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 struct cuse_server_dev* malloc (int,int /*<<< orphan*/ ,int) ; 
 int priv_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cuse_server_ioctl(struct cdev *dev, unsigned long cmd,
    caddr_t data, int fflag, struct thread *td)
{
	struct cuse_server *pcs;
	int error;

	error = cuse_server_get(&pcs);
	if (error != 0)
		return (error);

	switch (cmd) {
		struct cuse_client_command *pccmd;
		struct cuse_client *pcc;
		struct cuse_command *pcmd;
		struct cuse_alloc_info *pai;
		struct cuse_create_dev *pcd;
		struct cuse_server_dev *pcsd;
		struct cuse_data_chunk *pchk;
		int n;

	case CUSE_IOCTL_GET_COMMAND:
		pcmd = (void *)data;

		cuse_lock();

		while ((pccmd = TAILQ_FIRST(&pcs->head)) == NULL) {
			error = cv_wait_sig(&pcs->cv, &cuse_mtx);

			if (pcs->is_closing)
				error = ENXIO;

			if (error) {
				cuse_unlock();
				return (error);
			}
		}

		TAILQ_REMOVE(&pcs->head, pccmd, entry);
		pccmd->entry.tqe_prev = NULL;

		pccmd->entered = curthread;

		*pcmd = pccmd->sub;

		cuse_unlock();

		break;

	case CUSE_IOCTL_SYNC_COMMAND:

		cuse_lock();
		while ((pccmd = cuse_server_find_command(pcs, curthread)) != NULL) {

			/* send sync command */
			pccmd->entered = NULL;
			pccmd->error = *(int *)data;
			pccmd->command = CUSE_CMD_SYNC;

			/* signal peer, if any */
			cv_signal(&pccmd->cv);
		}
		cuse_unlock();

		break;

	case CUSE_IOCTL_ALLOC_UNIT:

		cuse_lock();
		n = cuse_alloc_unit_by_id_locked(pcs,
		    CUSE_ID_DEFAULT(0));
		cuse_unlock();

		if (n < 0)
			error = ENOMEM;
		else
			*(int *)data = n;
		break;

	case CUSE_IOCTL_ALLOC_UNIT_BY_ID:

		n = *(int *)data;

		n = (n & CUSE_ID_MASK);

		cuse_lock();
		n = cuse_alloc_unit_by_id_locked(pcs, n);
		cuse_unlock();

		if (n < 0)
			error = ENOMEM;
		else
			*(int *)data = n;
		break;

	case CUSE_IOCTL_FREE_UNIT:

		n = *(int *)data;

		n = CUSE_ID_DEFAULT(n);

		cuse_lock();
		error = cuse_free_unit_by_id_locked(pcs, n);
		cuse_unlock();
		break;

	case CUSE_IOCTL_FREE_UNIT_BY_ID:

		n = *(int *)data;

		cuse_lock();
		error = cuse_free_unit_by_id_locked(pcs, n);
		cuse_unlock();
		break;

	case CUSE_IOCTL_ALLOC_MEMORY:

		pai = (void *)data;

		if (pai->alloc_nr >= CUSE_ALLOC_UNIT_MAX) {
			error = ENOMEM;
			break;
		}
		if (pai->page_count >= CUSE_ALLOC_PAGES_MAX) {
			error = ENOMEM;
			break;
		}
		error = cuse_server_alloc_memory(pcs,
		    pai->alloc_nr, pai->page_count);
		break;

	case CUSE_IOCTL_FREE_MEMORY:
		pai = (void *)data;

		if (pai->alloc_nr >= CUSE_ALLOC_UNIT_MAX) {
			error = ENOMEM;
			break;
		}
		error = cuse_server_free_memory(pcs, pai->alloc_nr);
		break;

	case CUSE_IOCTL_GET_SIG:

		cuse_lock();
		pccmd = cuse_server_find_command(pcs, curthread);

		if (pccmd != NULL) {
			n = pccmd->got_signal;
			pccmd->got_signal = 0;
		} else {
			n = 0;
		}
		cuse_unlock();

		*(int *)data = n;

		break;

	case CUSE_IOCTL_SET_PFH:

		cuse_lock();
		pccmd = cuse_server_find_command(pcs, curthread);

		if (pccmd != NULL) {
			pcc = pccmd->client;
			for (n = 0; n != CUSE_CMD_MAX; n++) {
				pcc->cmds[n].sub.per_file_handle = *(uintptr_t *)data;
			}
		} else {
			error = ENXIO;
		}
		cuse_unlock();
		break;

	case CUSE_IOCTL_CREATE_DEV:

		error = priv_check(curthread, PRIV_DRIVER);
		if (error)
			break;

		pcd = (void *)data;

		/* filter input */

		pcd->devname[sizeof(pcd->devname) - 1] = 0;

		if (pcd->devname[0] == 0) {
			error = EINVAL;
			break;
		}
		cuse_str_filter(pcd->devname);

		pcd->permissions &= 0777;

		/* try to allocate a character device */

		pcsd = malloc(sizeof(*pcsd), M_CUSE, M_WAITOK | M_ZERO);

		if (pcsd == NULL) {
			error = ENOMEM;
			break;
		}
		pcsd->server = pcs;

		pcsd->user_dev = pcd->dev;

		pcsd->kern_dev = make_dev_credf(MAKEDEV_CHECKNAME,
		    &cuse_client_devsw, 0, NULL, pcd->user_id, pcd->group_id,
		    pcd->permissions, "%s", pcd->devname);

		if (pcsd->kern_dev == NULL) {
			free(pcsd, M_CUSE);
			error = ENOMEM;
			break;
		}
		pcsd->kern_dev->si_drv1 = pcsd;

		cuse_lock();
		TAILQ_INSERT_TAIL(&pcs->hdev, pcsd, entry);
		cuse_unlock();

		break;

	case CUSE_IOCTL_DESTROY_DEV:

		error = priv_check(curthread, PRIV_DRIVER);
		if (error)
			break;

		cuse_lock();

		error = EINVAL;

		pcsd = TAILQ_FIRST(&pcs->hdev);
		while (pcsd != NULL) {
			if (pcsd->user_dev == *(struct cuse_dev **)data) {
				TAILQ_REMOVE(&pcs->hdev, pcsd, entry);
				cuse_unlock();
				cuse_server_free_dev(pcsd);
				cuse_lock();
				error = 0;
				pcsd = TAILQ_FIRST(&pcs->hdev);
			} else {
				pcsd = TAILQ_NEXT(pcsd, entry);
			}
		}

		cuse_unlock();
		break;

	case CUSE_IOCTL_WRITE_DATA:
	case CUSE_IOCTL_READ_DATA:

		cuse_lock();
		pchk = (struct cuse_data_chunk *)data;

		pccmd = cuse_server_find_command(pcs, curthread);

		if (pccmd == NULL) {
			error = ENXIO;	/* invalid request */
		} else if (pchk->peer_ptr < CUSE_BUF_MIN_PTR) {
			error = EFAULT;	/* NULL pointer */
		} else if (pchk->peer_ptr < CUSE_BUF_MAX_PTR) {
			error = cuse_server_ioctl_copy_locked(pccmd,
			    pchk, cmd == CUSE_IOCTL_READ_DATA);
		} else {
			error = cuse_server_data_copy_locked(pccmd,
			    pchk, cmd == CUSE_IOCTL_READ_DATA);
		}
		cuse_unlock();
		break;

	case CUSE_IOCTL_SELWAKEUP:
		cuse_lock();
		/*
		 * We don't know which direction caused the event.
		 * Wakeup both!
		 */
		cuse_server_wakeup_all_client_locked(pcs);
		cuse_unlock();
		break;

	default:
		error = ENXIO;
		break;
	}
	return (error);
}
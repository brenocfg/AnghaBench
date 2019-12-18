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
struct ucred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct fuse_data {int ref; int /*<<< orphan*/  rename_lock; int /*<<< orphan*/  daemon_timeout; int /*<<< orphan*/  daemoncred; int /*<<< orphan*/  aw_head; int /*<<< orphan*/  aw_mtx; int /*<<< orphan*/  ms_mtx; TYPE_1__ ks_rsel; scalar_t__ ms_count; int /*<<< orphan*/  ms_head; struct cdev* fdev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DEFAULT_DAEMON_TIMEOUT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_FUSEMSG ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fuse_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

struct fuse_data *
fdata_alloc(struct cdev *fdev, struct ucred *cred)
{
	struct fuse_data *data;

	data = malloc(sizeof(struct fuse_data), M_FUSEMSG, M_WAITOK | M_ZERO);

	data->fdev = fdev;
	mtx_init(&data->ms_mtx, "fuse message list mutex", NULL, MTX_DEF);
	STAILQ_INIT(&data->ms_head);
	data->ms_count = 0;
	knlist_init_mtx(&data->ks_rsel.si_note, &data->ms_mtx);
	mtx_init(&data->aw_mtx, "fuse answer list mutex", NULL, MTX_DEF);
	TAILQ_INIT(&data->aw_head);
	data->daemoncred = crhold(cred);
	data->daemon_timeout = FUSE_DEFAULT_DAEMON_TIMEOUT;
	sx_init(&data->rename_lock, "fuse rename lock");
	data->ref = 1;

	return data;
}
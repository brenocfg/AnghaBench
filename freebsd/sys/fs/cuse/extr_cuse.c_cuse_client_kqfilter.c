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
struct knote {int kn_filter; int /*<<< orphan*/ * kn_fop; struct cuse_client* kn_hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct cuse_server {TYPE_1__ selinfo; } ;
struct cuse_client {int /*<<< orphan*/  cflags; struct cuse_server* server; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUSE_CLI_KNOTE_HAS_READ ; 
 int /*<<< orphan*/  CUSE_CLI_KNOTE_HAS_WRITE ; 
 int EINVAL ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int cuse_client_get (struct cuse_client**) ; 
 int /*<<< orphan*/  cuse_client_kqfilter_poll (struct cdev*,struct cuse_client*) ; 
 int /*<<< orphan*/  cuse_client_kqfilter_read_ops ; 
 int /*<<< orphan*/  cuse_client_kqfilter_write_ops ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int) ; 

__attribute__((used)) static int
cuse_client_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct cuse_client *pcc;
	struct cuse_server *pcs;
	int error;

	error = cuse_client_get(&pcc);
	if (error != 0)
		return (error);

	cuse_lock();
	pcs = pcc->server;
	switch (kn->kn_filter) {
	case EVFILT_READ:
		pcc->cflags |= CUSE_CLI_KNOTE_HAS_READ;
		kn->kn_hook = pcc;
		kn->kn_fop = &cuse_client_kqfilter_read_ops;
		knlist_add(&pcs->selinfo.si_note, kn, 1);
		break;
	case EVFILT_WRITE:
		pcc->cflags |= CUSE_CLI_KNOTE_HAS_WRITE;
		kn->kn_hook = pcc;
		kn->kn_fop = &cuse_client_kqfilter_write_ops;
		knlist_add(&pcs->selinfo.si_note, kn, 1);
		break;
	default:
		error = EINVAL;
		break;
	}
	cuse_unlock();

	if (error == 0)
		cuse_client_kqfilter_poll(dev, pcc);
	return (error);
}
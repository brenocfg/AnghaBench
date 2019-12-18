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
struct wrq_cookie {int dummy; } ;
struct tid_info {int ntids; int tid_base; int /*<<< orphan*/  hftid_lock; int /*<<< orphan*/  hftid_cv; int /*<<< orphan*/ * hftid_hash_4t; } ;
struct t4_filter {int const idx; int /*<<< orphan*/  fs; } ;
struct filter_entry {scalar_t__ valid; int const tid; int locked; int pending; int /*<<< orphan*/  fs; } ;
struct TYPE_3__ {int /*<<< orphan*/  abs_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctrlq; TYPE_1__ fwq; } ;
struct adapter {TYPE_2__ sge; struct tid_info tids; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  commit_wrq_wr (int /*<<< orphan*/ *,void*,struct wrq_cookie*) ; 
 scalar_t__ cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int del_hashfilter_wrlen () ; 
 int /*<<< orphan*/  free (struct filter_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  howmany (int const,int) ; 
 struct filter_entry* lookup_hftid (struct adapter*,int const) ; 
 int /*<<< orphan*/  mk_del_hashfilter_wr (int const,void*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 void* start_wrq_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wrq_cookie*) ; 

__attribute__((used)) static int
del_hashfilter(struct adapter *sc, struct t4_filter *t)
{
	struct tid_info *ti = &sc->tids;
	void *wr;
	struct filter_entry *f;
	struct wrq_cookie cookie;
	int rc;
	const int wrlen = del_hashfilter_wrlen();
	const int inv_tid = ti->ntids + ti->tid_base;

	MPASS(sc->tids.hftid_hash_4t != NULL);
	MPASS(sc->tids.ntids > 0);

	if (t->idx < sc->tids.tid_base || t->idx >= inv_tid)
		return (EINVAL);

	mtx_lock(&ti->hftid_lock);
	f = lookup_hftid(sc, t->idx);
	if (f == NULL || f->valid == 0) {
		rc = EINVAL;
		goto done;
	}
	MPASS(f->tid == t->idx);
	if (f->locked) {
		rc = EPERM;
		goto done;
	}
	if (f->pending) {
		rc = EBUSY;
		goto done;
	}
	wr = start_wrq_wr(&sc->sge.ctrlq[0], howmany(wrlen, 16), &cookie);
	if (wr == NULL) {
		rc = ENOMEM;
		goto done;
	}

	mk_del_hashfilter_wr(t->idx, wr, wrlen, sc->sge.fwq.abs_id);
	f->locked = 1;
	f->pending = 1;
	commit_wrq_wr(&sc->sge.ctrlq[0], wr, &cookie);
	t->fs = f->fs;	/* extra info for the caller */

	for (;;) {
		MPASS(f->locked);
		if (f->pending == 0) {
			if (f->valid) {
				f->locked = 0;
				rc = EIO;
			} else {
				rc = 0;
				free(f, M_CXGBE);
			}
			break;
		}
		if (cv_wait_sig(&ti->hftid_cv, &ti->hftid_lock) != 0) {
			f->locked = 0;
			rc = EINPROGRESS;
			break;
		}
	}
done:
	mtx_unlock(&ti->hftid_lock);
	return (rc);
}
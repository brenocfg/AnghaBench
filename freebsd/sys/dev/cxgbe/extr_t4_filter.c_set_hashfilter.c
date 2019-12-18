#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wrq_cookie {int dummy; } ;
struct TYPE_8__ {int pfvf_vld; int ovlan_vld; } ;
struct TYPE_7__ {int pfvf_vld; int ovlan_vld; } ;
struct TYPE_11__ {int hash; scalar_t__ type; TYPE_2__ mask; TYPE_1__ val; } ;
struct t4_filter {int idx; TYPE_5__ fs; } ;
struct smt_entry {int dummy; } ;
struct l2t_entry {int dummy; } ;
struct filter_entry {int locked; int pending; int tid; scalar_t__ valid; TYPE_5__ fs; struct smt_entry* smt; struct l2t_entry* l2te; } ;
struct TYPE_10__ {int /*<<< orphan*/  hftid_lock; int /*<<< orphan*/  hftid_cv; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ctrlq; } ;
struct adapter {TYPE_4__ tids; TYPE_3__ sge; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int __predict_false (int) ; 
 int /*<<< orphan*/  act_open_cpl_len16 (struct adapter*,scalar_t__) ; 
 int alloc_atid (struct adapter*,struct filter_entry*) ; 
 int /*<<< orphan*/  commit_wrq_wr (int /*<<< orphan*/ *,void*,struct wrq_cookie*) ; 
 scalar_t__ cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct filter_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_atid (struct adapter*,int) ; 
 int /*<<< orphan*/  hf_hashfn_4t (TYPE_5__*) ; 
 int /*<<< orphan*/  insert_hf (struct adapter*,struct filter_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_hf (struct adapter*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct filter_entry* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mk_act_open_req (struct adapter*,struct filter_entry*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mk_act_open_req6 (struct adapter*,struct filter_entry*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 void* start_wrq_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wrq_cookie*) ; 

__attribute__((used)) static int
set_hashfilter(struct adapter *sc, struct t4_filter *t, uint64_t ftuple,
    struct l2t_entry *l2te, struct smt_entry *smt)
{
	void *wr;
	struct wrq_cookie cookie;
	struct filter_entry *f;
	int rc, atid = -1;
	uint32_t hash;

	MPASS(t->fs.hash);
	/* Already validated against fconf, iconf */
	MPASS((t->fs.val.pfvf_vld & t->fs.val.ovlan_vld) == 0);
	MPASS((t->fs.mask.pfvf_vld & t->fs.mask.ovlan_vld) == 0);

	hash = hf_hashfn_4t(&t->fs);

	mtx_lock(&sc->tids.hftid_lock);
	if (lookup_hf(sc, &t->fs, hash) != NULL) {
		rc = EEXIST;
		goto done;
	}

	f = malloc(sizeof(*f), M_CXGBE, M_ZERO | M_NOWAIT);
	if (__predict_false(f == NULL)) {
		rc = ENOMEM;
		goto done;
	}
	f->fs = t->fs;
	f->l2te = l2te;
	f->smt = smt;

	atid = alloc_atid(sc, f);
	if (__predict_false(atid) == -1) {
		free(f, M_CXGBE);
		rc = EAGAIN;
		goto done;
	}
	MPASS(atid >= 0);

	wr = start_wrq_wr(&sc->sge.ctrlq[0], act_open_cpl_len16(sc, f->fs.type),
	    &cookie);
	if (wr == NULL) {
		free_atid(sc, atid);
		free(f, M_CXGBE);
		rc = ENOMEM;
		goto done;
	}
	if (f->fs.type)
		mk_act_open_req6(sc, f, atid, ftuple, wr);
	else
		mk_act_open_req(sc, f, atid, ftuple, wr);

	f->locked = 1; /* ithread mustn't free f if ioctl is still around. */
	f->pending = 1;
	f->tid = -1;
	insert_hf(sc, f, hash);
	commit_wrq_wr(&sc->sge.ctrlq[0], wr, &cookie);

	for (;;) {
		MPASS(f->locked);
		if (f->pending == 0) {
			if (f->valid) {
				rc = 0;
				f->locked = 0;
				t->idx = f->tid;
			} else {
				rc = f->tid;
				free(f, M_CXGBE);
			}
			break;
		}
		if (cv_wait_sig(&sc->tids.hftid_cv, &sc->tids.hftid_lock) != 0) {
			f->locked = 0;
			rc = EINPROGRESS;
			break;
		}
	}
done:
	mtx_unlock(&sc->tids.hftid_lock);
	return (rc);
}
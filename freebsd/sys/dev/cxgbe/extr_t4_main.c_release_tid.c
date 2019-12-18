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
struct wrqe {int dummy; } ;
struct sge_wrq {int dummy; } ;
struct cpl_tid_release {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_TID_RELEASE ; 
 int /*<<< orphan*/  INIT_TP_WR_MIT_CPL (struct cpl_tid_release*,int /*<<< orphan*/ ,int) ; 
 struct wrqe* alloc_wrqe (int,struct sge_wrq*) ; 
 int /*<<< orphan*/  queue_tid_release (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_wrq_tx (struct adapter*,struct wrqe*) ; 
 struct cpl_tid_release* wrtod (struct wrqe*) ; 

void
release_tid(struct adapter *sc, int tid, struct sge_wrq *ctrlq)
{
	struct wrqe *wr;
	struct cpl_tid_release *req;

	wr = alloc_wrqe(sizeof(*req), ctrlq);
	if (wr == NULL) {
		queue_tid_release(sc, tid);	/* defer */
		return;
	}
	req = wrtod(wr);

	INIT_TP_WR_MIT_CPL(req, CPL_TID_RELEASE, tid);

	t4_wrq_tx(sc, wr);
}
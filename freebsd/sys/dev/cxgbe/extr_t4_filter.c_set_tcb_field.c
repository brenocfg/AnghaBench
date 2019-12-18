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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct wrq_cookie {int dummy; } ;
struct cpl_set_tcb_field {void* val; void* mask; void* word_cookie; void* reply_ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  abs_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctrlq; TYPE_1__ fwq; } ;
struct adapter {TYPE_2__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_COOKIE_HASHFILTER ; 
 int /*<<< orphan*/  CPL_SET_TCB_FIELD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_TP_WR_MIT_CPL (struct cpl_set_tcb_field*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V_COOKIE (int /*<<< orphan*/ ) ; 
 int V_NO_REPLY (int) ; 
 int V_QUEUENO (int /*<<< orphan*/ ) ; 
 int V_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct cpl_set_tcb_field*,int) ; 
 int /*<<< orphan*/  commit_wrq_wr (int /*<<< orphan*/ *,struct cpl_set_tcb_field*,struct wrq_cookie*) ; 
 int /*<<< orphan*/  howmany (int,int) ; 
 void* htobe16 (int) ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 
 struct cpl_set_tcb_field* start_wrq_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wrq_cookie*) ; 

__attribute__((used)) static int
set_tcb_field(struct adapter *sc, u_int tid, uint16_t word, uint64_t mask,
    uint64_t val, int no_reply)
{
	struct wrq_cookie cookie;
	struct cpl_set_tcb_field *req;

	req = start_wrq_wr(&sc->sge.ctrlq[0], howmany(sizeof(*req), 16), &cookie);
	if (req == NULL)
		return (ENOMEM);
	bzero(req, sizeof(*req));
	INIT_TP_WR_MIT_CPL(req, CPL_SET_TCB_FIELD, tid);
	if (no_reply == 0) {
		req->reply_ctrl = htobe16(V_QUEUENO(sc->sge.fwq.abs_id) |
		    V_NO_REPLY(0));
	} else
		req->reply_ctrl = htobe16(V_NO_REPLY(1));
	req->word_cookie = htobe16(V_WORD(word) | V_COOKIE(CPL_COOKIE_HASHFILTER));
	req->mask = htobe64(mask);
	req->val = htobe64(val);
	commit_wrq_wr(&sc->sge.ctrlq[0], req, &cookie);

	return (0);
}
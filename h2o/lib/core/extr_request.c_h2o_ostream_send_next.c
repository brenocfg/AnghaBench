#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_7__ {TYPE_2__* _ostr_top; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  (* do_send ) (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ h2o_ostream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

void h2o_ostream_send_next(h2o_ostream_t *ostream, h2o_req_t *req, h2o_sendvec_t *bufs, size_t bufcnt, h2o_send_state_t state)
{
    if (!h2o_send_state_is_in_progress(state)) {
        assert(req->_ostr_top == ostream);
        req->_ostr_top = ostream->next;
    }
    ostream->next->do_send(ostream->next, req, bufs, bufcnt, state);
}
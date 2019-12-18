#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_5__ {TYPE_2__* _ostr_top; int /*<<< orphan*/ * _generator; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* do_send ) (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_sendvec(h2o_req_t *req, h2o_sendvec_t *bufs, size_t bufcnt, h2o_send_state_t state)
{
    assert(req->_generator != NULL);

    if (!h2o_send_state_is_in_progress(state))
        req->_generator = NULL;

    req->_ostr_top->do_send(req->_ostr_top, req, bufs, bufcnt, state);
}
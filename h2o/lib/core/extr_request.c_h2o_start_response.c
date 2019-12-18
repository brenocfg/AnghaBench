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
struct TYPE_7__ {int /*<<< orphan*/  _ostr_top; TYPE_2__* prefilters; int /*<<< orphan*/ * _generator; } ;
typedef  TYPE_1__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* on_setup_ostream ) (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_setup_next_ostream (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retain_original_response (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

void h2o_start_response(h2o_req_t *req, h2o_generator_t *generator)
{
    retain_original_response(req);

    /* set generator */
    assert(req->_generator == NULL);
    req->_generator = generator;

    /* setup response filters */
    if (req->prefilters != NULL) {
        req->prefilters->on_setup_ostream(req->prefilters, req, &req->_ostr_top);
    } else {
        h2o_setup_next_ostream(req, &req->_ostr_top);
    }
}
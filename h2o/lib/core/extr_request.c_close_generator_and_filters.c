#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* _ostr_top; TYPE_4__* _generator; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* stop ) (TYPE_4__*,TYPE_1__*) ;} ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  (* stop ) (TYPE_2__*,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void close_generator_and_filters(h2o_req_t *req)
{
    /* close the generator if it is still open */
    if (req->_generator != NULL) {
        /* close generator */
        if (req->_generator->stop != NULL)
            req->_generator->stop(req->_generator, req);
        req->_generator = NULL;
    }
    /* close the ostreams still open */
    while (req->_ostr_top->next != NULL) {
        if (req->_ostr_top->stop != NULL)
            req->_ostr_top->stop(req->_ostr_top, req);
        req->_ostr_top = req->_ostr_top->next;
    }
}
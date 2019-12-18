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
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_8__ {int /*<<< orphan*/ * send_informational; int /*<<< orphan*/ * stop; int /*<<< orphan*/ * do_send; struct TYPE_8__* next; } ;
typedef  TYPE_2__ h2o_ostream_t ;

/* Variables and functions */
 TYPE_2__* h2o_mem_alloc_pool_aligned (int /*<<< orphan*/ *,size_t,size_t) ; 

h2o_ostream_t *h2o_add_ostream(h2o_req_t *req, size_t alignment, size_t sz, h2o_ostream_t **slot)
{
    h2o_ostream_t *ostr = h2o_mem_alloc_pool_aligned(&req->pool, alignment, sz);
    ostr->next = *slot;
    ostr->do_send = NULL;
    ostr->stop = NULL;
    ostr->send_informational = NULL;

    *slot = ostr;

    return ostr;
}
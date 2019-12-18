#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ opcode; } ;
struct TYPE_18__ {scalar_t__ I; } ;
struct TYPE_20__ {TYPE_2__ data_out; TYPE_1__ bhs; } ;
struct TYPE_21__ {TYPE_3__ ipdu; } ;
struct TYPE_22__ {scalar_t__ len; TYPE_4__ pdu; } ;
typedef  TYPE_5__ pduq_t ;
struct TYPE_23__ {int flags; int /*<<< orphan*/  io_mtx; } ;
typedef  TYPE_6__ isc_session_t ;

/* Variables and functions */
 scalar_t__ ISCSI_WRITE_DATA ; 
 int ISC_OQNOTEMPTY ; 
 int ISC_OWAITING ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  i_nqueue_csnd (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  i_nqueue_isnd (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  i_nqueue_wsnd (TYPE_6__*,TYPE_5__*) ; 
 int i_prepPDU (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

int
isc_qout(isc_session_t *sp, pduq_t *pq)
{
     int error = 0;

     debug_called(8);

     if(pq->len == 0 && (error = i_prepPDU(sp, pq)))
	  return error;

     if(pq->pdu.ipdu.bhs.I)
	  i_nqueue_isnd(sp, pq);
     else
     if(pq->pdu.ipdu.data_out.opcode == ISCSI_WRITE_DATA)
	  i_nqueue_wsnd(sp, pq);
     else
	  i_nqueue_csnd(sp, pq);

     sdebug(5, "enqued: pq=%p", pq);

     mtx_lock(&sp->io_mtx);
     sp->flags |= ISC_OQNOTEMPTY;
     if(sp->flags & ISC_OWAITING)
	  wakeup(&sp->flags);
     mtx_unlock(&sp->io_mtx);

     return error;
}
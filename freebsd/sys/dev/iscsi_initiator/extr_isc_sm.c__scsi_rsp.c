#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  itt; } ;
struct TYPE_19__ {TYPE_1__ bhs; } ;
struct TYPE_17__ {TYPE_2__ ipdu; } ;
struct TYPE_20__ {TYPE_12__ pdu; } ;
typedef  TYPE_3__ pduq_t ;
struct TYPE_21__ {int /*<<< orphan*/  isc; int /*<<< orphan*/  sid; } ;
typedef  TYPE_4__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  i_acked_hld (TYPE_4__*,TYPE_12__*) ; 
 TYPE_3__* i_search_hld (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_done (TYPE_4__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdu_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  xdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsi_rsp(isc_session_t *sp, pduq_t *pq)
{
     pduq_t	*opq;

     debug_called(8);
     opq = i_search_hld(sp, pq->pdu.ipdu.bhs.itt, 0);
     debug(5, "itt=%x pq=%p opq=%p", ntohl(pq->pdu.ipdu.bhs.itt), pq, opq);
     if(opq != NULL) {
	  iscsi_done(sp, opq, pq);
	  i_acked_hld(sp, &pq->pdu);
     }
     else
	  xdebug("%d] we lost something itt=%x",
		 sp->sid, ntohl(pq->pdu.ipdu.bhs.itt));
     pdu_free(sp->isc, pq);
}
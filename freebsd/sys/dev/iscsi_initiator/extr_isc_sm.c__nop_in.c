#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ maxcmd; } ;
struct TYPE_20__ {int /*<<< orphan*/  mbz; TYPE_2__ sn; } ;
struct TYPE_23__ {int I; int F; int /*<<< orphan*/  opcode; } ;
struct TYPE_21__ {int itt; int ttt; } ;
struct TYPE_16__ {TYPE_5__ nop_out; TYPE_8__ bhs; TYPE_6__ nop_in; } ;
struct TYPE_19__ {scalar_t__ ds_len; TYPE_1__ ipdu; } ;
struct TYPE_18__ {TYPE_4__ pdu; } ;
typedef  TYPE_3__ pduq_t ;
typedef  TYPE_4__ pdu_t ;
typedef  TYPE_5__ nop_out_t ;
typedef  TYPE_6__ nop_in_t ;
struct TYPE_22__ {int flags; int /*<<< orphan*/  isc; int /*<<< orphan*/  rsp; int /*<<< orphan*/  sid; } ;
typedef  TYPE_7__ isc_session_t ;
typedef  TYPE_8__ bhs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_NOP_OUT ; 
 int ISC_WAIT4PING ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  i_nqueue_rsp (TYPE_7__*,TYPE_3__*) ; 
 int /*<<< orphan*/  isc_qout (TYPE_7__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdu_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sdebug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdebug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_nop_in(isc_session_t *sp, pduq_t *pq)
{
     pdu_t	*pp = &pq->pdu;
     nop_in_t	*nop_in = &pp->ipdu.nop_in;
     bhs_t	*bhs = &pp->ipdu.bhs;

     debug_called(8);

     sdebug(5, "itt=%x ttt=%x", htonl(nop_in->itt), htonl(nop_in->ttt));
     if(nop_in->itt == -1) {
	  if(pp->ds_len != 0) {
	       /*
		| according to RFC 3720 this should be zero
		| what to do if not?
		*/
	       xdebug("%d] dslen not zero", sp->sid);
	  }
	  if(nop_in->ttt != -1) {
	       nop_out_t	*nop_out;
	       /*
		| target wants a nop_out
	        */
	       bhs->opcode = ISCSI_NOP_OUT;
	       bhs->I = 1;
	       bhs->F = 1;
	       /*
		| we are reusing the pdu, so bhs->ttt == nop_in->ttt;
		| and need to zero out 'Reserved'
		| small cludge here.
	        */
	       nop_out = &pp->ipdu.nop_out;
	       nop_out->sn.maxcmd = 0;
	       memset(nop_out->mbz, 0, sizeof(nop_out->mbz));
	       (void)isc_qout(sp, pq); //XXX: should check return?
	       return;
	  }
	  //else {
	       // just making noise?
	       // see 10.9.1: target does not want and answer.
	  //}

     } else
     if(nop_in->ttt == -1) {
	  /*
	   | it is an answer to a nop_in from us
	   */
	  if(nop_in->itt != -1) {
#ifdef ISC_WAIT4PING
	       // XXX: MUTEX please
	       if(sp->flags & ISC_WAIT4PING) {
		    i_nqueue_rsp(sp, pq);
		    wakeup(&sp->rsp);
		    return;
	       }
#endif
	  }
     }
     /*
      | drop it
      */
     pdu_free(sp->isc, pq);
     return;
}
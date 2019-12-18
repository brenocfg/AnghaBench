#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pduq_t ;
struct TYPE_8__ {int /*<<< orphan*/  isc; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/ * i_dqueue_hld (TYPE_1__*) ; 
 int /*<<< orphan*/ * i_dqueue_rsp (TYPE_1__*) ; 
 int /*<<< orphan*/ * i_dqueue_rsv (TYPE_1__*) ; 
 int /*<<< orphan*/ * i_dqueue_snd (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * i_dqueue_wsnd (TYPE_1__*) ; 
 int /*<<< orphan*/  pdu_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdebug (char*,int) ; 

int
i_pdu_flush(isc_session_t *sp)
{
     int	n = 0;
     pduq_t	*pq;

     debug_called(8);
     while((pq = i_dqueue_rsp(sp)) != NULL) {
	  pdu_free(sp->isc, pq);
	  n++;
     }
     while((pq = i_dqueue_rsv(sp)) != NULL) {
	  pdu_free(sp->isc, pq);
	  n++;
     }
     while((pq = i_dqueue_snd(sp, -1)) != NULL) {
	  pdu_free(sp->isc, pq);
	  n++;
     }
     while((pq = i_dqueue_hld(sp)) != NULL) {
	  pdu_free(sp->isc, pq);
	  n++;
     }
     while((pq = i_dqueue_wsnd(sp)) != NULL) {
	  pdu_free(sp->isc, pq);
	  n++;
     }
     if(n != 0)
	  xdebug("%d pdus recovered, should have been ZERO!", n);
     return n;
}
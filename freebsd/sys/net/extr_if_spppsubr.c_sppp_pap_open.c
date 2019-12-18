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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int opts; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_configure; } ;
struct TYPE_6__ {scalar_t__ proto; } ;
struct TYPE_7__ {scalar_t__ proto; } ;
struct sppp {TYPE_3__ lcp; int /*<<< orphan*/  pap_my_to_ch; TYPE_1__ myauth; int /*<<< orphan*/ * rst_counter; TYPE_2__ hisauth; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* scr ) (struct sppp*) ;} ;

/* Variables and functions */
 size_t IDX_PAP ; 
 int LCP_OPT_AUTH_PROTO ; 
 scalar_t__ PPP_PAP ; 
 int /*<<< orphan*/  STATE_REQ_SENT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 TYPE_4__ pap ; 
 int /*<<< orphan*/  sppp_cp_change_state (TYPE_4__*,struct sppp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sppp_pap_my_TO ; 
 int /*<<< orphan*/  stub1 (struct sppp*) ; 

__attribute__((used)) static void
sppp_pap_open(struct sppp *sp)
{
	if (sp->hisauth.proto == PPP_PAP &&
	    (sp->lcp.opts & (1 << LCP_OPT_AUTH_PROTO)) != 0) {
		/* we are authenticator for PAP, start our timer */
		sp->rst_counter[IDX_PAP] = sp->lcp.max_configure;
		sppp_cp_change_state(&pap, sp, STATE_REQ_SENT);
	}
	if (sp->myauth.proto == PPP_PAP) {
		/* we are peer, send a request, and start a timer */
		pap.scr(sp);
		callout_reset(&sp->pap_my_to_ch, sp->lcp.timeout,
			      sppp_pap_my_TO, (void *)sp);
	}
}
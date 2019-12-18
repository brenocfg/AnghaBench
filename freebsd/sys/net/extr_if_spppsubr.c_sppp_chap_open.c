#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int opts; int /*<<< orphan*/  max_configure; } ;
struct TYPE_5__ {scalar_t__ proto; } ;
struct sppp {TYPE_2__ lcp; int /*<<< orphan*/ * rst_counter; TYPE_1__ myauth; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* scr ) (struct sppp*) ;} ;

/* Variables and functions */
 size_t IDX_CHAP ; 
 int LCP_OPT_AUTH_PROTO ; 
 scalar_t__ PPP_CHAP ; 
 int /*<<< orphan*/  STATE_REQ_SENT ; 
 TYPE_3__ chap ; 
 int /*<<< orphan*/  sppp_cp_change_state (TYPE_3__*,struct sppp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sppp*) ; 

__attribute__((used)) static void
sppp_chap_open(struct sppp *sp)
{
	if (sp->myauth.proto == PPP_CHAP &&
	    (sp->lcp.opts & (1 << LCP_OPT_AUTH_PROTO)) != 0) {
		/* we are authenticator for CHAP, start it */
		chap.scr(sp);
		sp->rst_counter[IDX_CHAP] = sp->lcp.max_configure;
		sppp_cp_change_state(&chap, sp, STATE_REQ_SENT);
	}
	/* nothing to be done if we are peer, await a challenge */
}
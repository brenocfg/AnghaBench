#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int opts; int timeout; int max_terminate; int max_configure; int max_failure; int /*<<< orphan*/  their_mru; int /*<<< orphan*/  mru; scalar_t__ protos; scalar_t__ magic; } ;
struct sppp {int /*<<< orphan*/ * ch; TYPE_1__ lcp; scalar_t__* pp_rseq; scalar_t__* pp_seq; scalar_t__* fail_counter; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 size_t IDX_LCP ; 
 int LCP_OPT_MAGIC ; 
 int /*<<< orphan*/  PP_MTU ; 
 int /*<<< orphan*/  STATE_INITIAL ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int hz ; 

__attribute__((used)) static void
sppp_lcp_init(struct sppp *sp)
{
	sp->lcp.opts = (1 << LCP_OPT_MAGIC);
	sp->lcp.magic = 0;
	sp->state[IDX_LCP] = STATE_INITIAL;
	sp->fail_counter[IDX_LCP] = 0;
	sp->pp_seq[IDX_LCP] = 0;
	sp->pp_rseq[IDX_LCP] = 0;
	sp->lcp.protos = 0;
	sp->lcp.mru = sp->lcp.their_mru = PP_MTU;

	/* Note that these values are  relevant for all control protocols */
	sp->lcp.timeout = 3 * hz;
	sp->lcp.max_terminate = 2;
	sp->lcp.max_configure = 10;
	sp->lcp.max_failure = 10;
 	callout_init(&sp->ch[IDX_LCP], 1);
}
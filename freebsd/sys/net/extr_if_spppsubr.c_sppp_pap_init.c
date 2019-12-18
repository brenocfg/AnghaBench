#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sppp {int /*<<< orphan*/  pap_my_to_ch; int /*<<< orphan*/ * ch; scalar_t__* pp_rseq; scalar_t__* pp_seq; scalar_t__* fail_counter; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 size_t IDX_PAP ; 
 int /*<<< orphan*/  STATE_CLOSED ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sppp_pap_init(struct sppp *sp)
{
	/* PAP doesn't have STATE_INITIAL at all. */
	sp->state[IDX_PAP] = STATE_CLOSED;
	sp->fail_counter[IDX_PAP] = 0;
	sp->pp_seq[IDX_PAP] = 0;
	sp->pp_rseq[IDX_PAP] = 0;
 	callout_init(&sp->ch[IDX_PAP], 1);
 	callout_init(&sp->pap_my_to_ch, 1);
}
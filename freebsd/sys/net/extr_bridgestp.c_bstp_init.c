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
struct bstp_state {int bs_running; int /*<<< orphan*/  bs_bstpcallout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_tick ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bstp_state*) ; 
 int /*<<< orphan*/  hz ; 

void
bstp_init(struct bstp_state *bs)
{
	BSTP_LOCK(bs);
	callout_reset(&bs->bs_bstpcallout, hz, bstp_tick, bs);
	bs->bs_running = 1;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
}
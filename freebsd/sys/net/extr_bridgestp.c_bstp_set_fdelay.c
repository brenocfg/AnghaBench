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
struct bstp_state {int bs_bridge_fdelay; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_MAX_FORWARD_DELAY ; 
 int BSTP_MIN_FORWARD_DELAY ; 
 int BSTP_TICK_VAL ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 

int
bstp_set_fdelay(struct bstp_state *bs, int t)
{
	/* convert seconds to ticks */
	t *= BSTP_TICK_VAL;

	if (t < BSTP_MIN_FORWARD_DELAY || t > BSTP_MAX_FORWARD_DELAY)
		return (EINVAL);

	BSTP_LOCK(bs);
	bs->bs_bridge_fdelay = t;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
	return (0);
}
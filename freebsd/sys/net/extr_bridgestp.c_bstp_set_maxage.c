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
struct bstp_state {int bs_bridge_max_age; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_MAX_MAX_AGE ; 
 int BSTP_MIN_MAX_AGE ; 
 int BSTP_TICK_VAL ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 

int
bstp_set_maxage(struct bstp_state *bs, int t)
{
	/* convert seconds to ticks */
	t *= BSTP_TICK_VAL;

	if (t < BSTP_MIN_MAX_AGE || t > BSTP_MAX_MAX_AGE)
		return (EINVAL);

	BSTP_LOCK(bs);
	bs->bs_bridge_max_age = t;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
	return (0);
}
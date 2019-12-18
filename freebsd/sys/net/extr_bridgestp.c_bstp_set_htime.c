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
struct bstp_state {scalar_t__ bs_protover; int bs_bridge_htime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_MAX_HELLO_TIME ; 
 int BSTP_MIN_HELLO_TIME ; 
 scalar_t__ BSTP_PROTO_STP ; 
 int BSTP_TICK_VAL ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 

int
bstp_set_htime(struct bstp_state *bs, int t)
{
	/* convert seconds to ticks */
	t *=  BSTP_TICK_VAL;

	/* value can only be changed in leagacy stp mode */
	if (bs->bs_protover != BSTP_PROTO_STP)
		return (EPERM);

	if (t < BSTP_MIN_HELLO_TIME || t > BSTP_MAX_HELLO_TIME)
		return (EINVAL);

	BSTP_LOCK(bs);
	bs->bs_bridge_htime = t;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
	return (0);
}
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
typedef  int /*<<< orphan*/  u_int16_t ;
struct initiator_state {int /*<<< orphan*/  pending_ua; } ;
typedef  int cam_status ;

/* Variables and functions */
 int MAX_INITIATORS ; 
 int /*<<< orphan*/  UA_POWER_ON ; 
 int /*<<< orphan*/  bzero (struct initiator_state*,int) ; 
 int init_inquiry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct initiator_state* tcmd_get_istate (int) ; 

cam_status
tcmd_init(u_int16_t req_inq_flags, u_int16_t sim_inq_flags)
{
	struct initiator_state *istate;
	int i, ret;

	/* Initialize our inquiry data */
	ret = init_inquiry(req_inq_flags, sim_inq_flags);
	if (ret != 0)
        	return (ret);

	/* We start out life with a UA to indicate power-on/reset. */
	for (i = 0; i < MAX_INITIATORS; i++) {
		istate = tcmd_get_istate(i);
		bzero(istate, sizeof(*istate));
		istate->pending_ua = UA_POWER_ON;
	}

	return (0);
}
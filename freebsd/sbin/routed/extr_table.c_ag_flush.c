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
struct ag_info {int ag_mask; int ag_dst_h; int ag_state; scalar_t__ ag_gate; scalar_t__ ag_pref; scalar_t__ ag_tag; scalar_t__ ag_nhop; struct ag_info* ag_cors; } ;
typedef  int naddr ;

/* Variables and functions */
 int AGS_CORS_GATE ; 
 int AGS_FINE_GATE ; 
 int AGS_REDUN0 ; 
 int AGS_REDUN1 ; 
 int AGS_SUPPRESS ; 
 scalar_t__ AG_IS_REDUN (int) ; 
 int /*<<< orphan*/  CHECK_AG () ; 
 int /*<<< orphan*/  ag_del (struct ag_info*) ; 
 struct ag_info* ag_finest ; 
 int /*<<< orphan*/  ag_out (struct ag_info*,void (*) (struct ag_info*)) ; 

void
ag_flush(naddr lim_dst_h,		/* flush routes to here */
	 naddr lim_mask,		/* matching this mask */
	 void (*out)(struct ag_info *))
{
	struct ag_info *ag, *ag_cors;
	naddr dst_h;


	for (ag = ag_finest;
	     ag != NULL && ag->ag_mask >= lim_mask;
	     ag = ag_cors) {
		ag_cors = ag->ag_cors;

		/* work on only the specified routes */
		dst_h = ag->ag_dst_h;
		if ((dst_h & lim_mask) != lim_dst_h)
			continue;

		if (!(ag->ag_state & AGS_SUPPRESS))
			ag_out(ag, out);

		else for ( ; ; ag_cors = ag_cors->ag_cors) {
			/* Look for a route that can suppress the
			 * current route */
			if (ag_cors == NULL) {
				/* failed, so output it and look for
				 * another route to work on
				 */
				ag_out(ag, out);
				break;
			}

			if ((dst_h & ag_cors->ag_mask) == ag_cors->ag_dst_h) {
				/* We found a route with a coarser mask that
				 * aggregates the current target.
				 *
				 * If it has a different next hop, it
				 * cannot replace the target, so output
				 * the target.
				 */
				if (ag->ag_gate != ag_cors->ag_gate
				    && !(ag->ag_state & AGS_FINE_GATE)
				    && !(ag_cors->ag_state & AGS_CORS_GATE)) {
					ag_out(ag, out);
					break;
				}

				/* If the coarse route has a good enough
				 * metric, it suppresses the target.
				 * If the suppressed target was redundant,
				 * then mark the suppressor redundant.
				 */
				if (ag_cors->ag_pref <= ag->ag_pref) {
				    if (AG_IS_REDUN(ag->ag_state)
					&& ag_cors->ag_mask==ag->ag_mask<<1) {
					if (ag_cors->ag_dst_h == dst_h)
					    ag_cors->ag_state |= AGS_REDUN0;
					else
					    ag_cors->ag_state |= AGS_REDUN1;
				    }
				    if (ag->ag_tag != ag_cors->ag_tag)
					    ag_cors->ag_tag = 0;
				    if (ag->ag_nhop != ag_cors->ag_nhop)
					    ag_cors->ag_nhop = 0;
				    break;
				}
			}
		}

		/* That route has either been output or suppressed */
		ag_cors = ag->ag_cors;
		ag_del(ag);
	}

	CHECK_AG();
}
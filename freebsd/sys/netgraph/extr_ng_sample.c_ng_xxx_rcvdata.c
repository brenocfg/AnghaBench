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
typedef  TYPE_3__* xxx_p ;
struct mbuf {int dummy; } ;
struct XXX_hookinfo {int dlci; int channel; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_6__ {scalar_t__ hook; } ;
struct TYPE_7__ {TYPE_2__ downstream_hook; int /*<<< orphan*/  packets_in; TYPE_1__* channel; int /*<<< orphan*/  packets_out; } ;
struct TYPE_5__ {int dlci; scalar_t__ hook; } ;

/* Variables and functions */
 int ENETUNREACH ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_FWD_NEW_DATA (int,int /*<<< orphan*/ ,scalar_t__,struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 scalar_t__ NG_HOOK_PRIVATE (scalar_t__) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int XXX_NUM_DLCIS ; 

__attribute__((used)) static int
ng_xxx_rcvdata(hook_p hook, item_p item )
{
	const xxx_p xxxp = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	int chan = -2;
	int dlci = -2;
	int error;
	struct mbuf *m;

	NGI_GET_M(item, m);
	if (NG_HOOK_PRIVATE(hook)) {
		dlci = ((struct XXX_hookinfo *) NG_HOOK_PRIVATE(hook))->dlci;
		chan = ((struct XXX_hookinfo *) NG_HOOK_PRIVATE(hook))->channel;
		if (dlci != -1) {
			/* If received on a DLCI hook process for this
			 * channel and pass it to the downstream module.
			 * Normally one would add a multiplexing header at
			 * the front here */
			/* M_PREPEND(....)	; */
			/* mtod(m, xxxxxx)->dlci = dlci; */
			NG_FWD_NEW_DATA(error, item,
				xxxp->downstream_hook.hook, m);
			xxxp->packets_out++;
		} else {
			/* data came from the multiplexed link */
			dlci = 1;	/* get dlci from header */
			/* madjust(....) *//* chop off header */
			for (chan = 0; chan < XXX_NUM_DLCIS; chan++)
				if (xxxp->channel[chan].dlci == dlci)
					break;
			if (chan == XXX_NUM_DLCIS) {
				NG_FREE_ITEM(item);
				NG_FREE_M(m);
				return (ENETUNREACH);
			}
			/* If we were called at splnet, use the following:
			 * NG_SEND_DATA_ONLY(error, otherhook, m); if this
			 * node is running at some SPL other than SPLNET
			 * then you should use instead: error =
			 * ng_queueit(otherhook, m, NULL); m = NULL;
			 * This queues the data using the standard NETISR
			 * system and schedules the data to be picked
			 * up again once the system has moved to SPLNET and
			 * the processing of the data can continue. After
			 * these are run 'm' should be considered
			 * as invalid and NG_SEND_DATA actually zaps them. */
			NG_FWD_NEW_DATA(error, item,
				xxxp->channel[chan].hook, m);
			xxxp->packets_in++;
		}
	} else {
		/* It's the debug hook, throw it away.. */
		if (hook == xxxp->downstream_hook.hook) {
			NG_FREE_ITEM(item);
			NG_FREE_M(m);
		}
	}
	return 0;
}
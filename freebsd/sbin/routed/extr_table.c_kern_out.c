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
struct khash {int k_state; scalar_t__ k_gate; scalar_t__ k_metric; } ;
struct ag_info {scalar_t__ ag_metric; int ag_state; scalar_t__ ag_gate; int /*<<< orphan*/  ag_mask; int /*<<< orphan*/  ag_dst_h; } ;

/* Variables and functions */
 int AGS_GATEWAY ; 
 scalar_t__ HOPCNT_INFINITY ; 
 int KS_ADD ; 
 int KS_CHANGE ; 
 int KS_DELETE ; 
 int KS_DELETED ; 
 int KS_DEL_ADD ; 
 int KS_DYNAMIC ; 
 int KS_GATEWAY ; 
 int KS_NEW ; 
 int KS_STATIC ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct khash* kern_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct khash* kern_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kern_out(struct ag_info *ag)
{
	struct khash *k;


	/* Do not install bad routes if they are not already present.
	 * This includes routes that had RS_NET_SYN for interfaces that
	 * recently died.
	 */
	if (ag->ag_metric == HOPCNT_INFINITY) {
		k = kern_find(htonl(ag->ag_dst_h), ag->ag_mask, 0);
		if (k == NULL)
			return;
	} else {
		k = kern_add(htonl(ag->ag_dst_h), ag->ag_mask);
	}

	if (k->k_state & KS_NEW) {
		/* will need to add new entry to the kernel table */
		k->k_state = KS_ADD;
		if (ag->ag_state & AGS_GATEWAY)
			k->k_state |= KS_GATEWAY;
		k->k_gate = ag->ag_gate;
		k->k_metric = ag->ag_metric;
		return;
	}

	if (k->k_state & KS_STATIC)
		return;

	/* modify existing kernel entry if necessary */
	if (k->k_gate != ag->ag_gate
	    || k->k_metric != ag->ag_metric) {
		/* Must delete bad interface routes etc. to change them. */
		if (k->k_metric == HOPCNT_INFINITY)
			k->k_state |= KS_DEL_ADD;
		k->k_gate = ag->ag_gate;
		k->k_metric = ag->ag_metric;
		k->k_state |= KS_CHANGE;
	}

	/* If the daemon thinks the route should exist, forget
	 * about any redirections.
	 * If the daemon thinks the route should exist, eventually
	 * override manual intervention by the operator.
	 */
	if ((k->k_state & (KS_DYNAMIC | KS_DELETED)) != 0) {
		k->k_state &= ~KS_DYNAMIC;
		k->k_state |= (KS_ADD | KS_DEL_ADD);
	}

	if ((k->k_state & KS_GATEWAY)
	    && !(ag->ag_state & AGS_GATEWAY)) {
		k->k_state &= ~KS_GATEWAY;
		k->k_state |= (KS_ADD | KS_DEL_ADD);
	} else if (!(k->k_state & KS_GATEWAY)
		   && (ag->ag_state & AGS_GATEWAY)) {
		k->k_state |= KS_GATEWAY;
		k->k_state |= (KS_ADD | KS_DEL_ADD);
	}

	/* Deleting-and-adding is necessary to change aspects of a route.
	 * Just delete instead of deleting and then adding a bad route.
	 * Otherwise, we want to keep the route in the kernel.
	 */
	if (k->k_metric == HOPCNT_INFINITY
	    && (k->k_state & KS_DEL_ADD))
		k->k_state |= KS_DELETE;
	else
		k->k_state &= ~KS_DELETE;
#undef RT
}
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
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 scalar_t__ NG_NODE_NOT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ppp_frag_checkstale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ppp_start_frag_timer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_ppp_frag_timeout(node_p node, hook_p hook, void *arg1, int arg2)
{
	/* XXX: is this needed? */
	if (NG_NODE_NOT_VALID(node))
		return;

	/* Scan the fragment queue */
	ng_ppp_frag_checkstale(node);

	/* Start timer again */
	ng_ppp_start_frag_timer(node);
}
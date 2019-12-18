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
typedef  scalar_t__ ng_ID_t ;
typedef  int /*<<< orphan*/  item_p ;
typedef  scalar_t__ NGI_RETADDR ;

/* Variables and functions */
 scalar_t__ ng_node2ID (int /*<<< orphan*/ ) ; 

void
ng_replace_retaddr(node_p here, item_p item, ng_ID_t retaddr)
{
	if (retaddr) {
		NGI_RETADDR(item) = retaddr;
	} else {
		/*
		 * The old return address should be ok.
		 * If there isn't one, use the address here.
		 */
		NGI_RETADDR(item) = ng_node2ID(here);
	}
}
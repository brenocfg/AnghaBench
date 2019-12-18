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
typedef  int /*<<< orphan*/ * node_p ;
typedef  int /*<<< orphan*/  ng_ID_t ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_DEBUG_CHECKS ; 
 int /*<<< orphan*/  NGI_SET_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGI_SET_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RETADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ng_path2noderef (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int
ng_address_path(node_p here, item_p item, const char *address, ng_ID_t retaddr)
{
	node_p	dest = NULL;
	hook_p	hook = NULL;
	int	error;

	ITEM_DEBUG_CHECKS;
	/*
	 * Note that ng_path2noderef increments the reference count
	 * on the node for us if it finds one. So we don't have to.
	 */
	error = ng_path2noderef(here, address, &dest, &hook);
	if (error) {
		NG_FREE_ITEM(item);
		return (error);
	}
	NGI_SET_NODE(item, dest);
	if (hook)
		NGI_SET_HOOK(item, hook);

	SET_RETADDR(item, here, retaddr);
	return (0);
}
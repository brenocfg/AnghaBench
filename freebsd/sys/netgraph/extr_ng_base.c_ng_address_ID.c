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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ITEM_DEBUG_CHECKS ; 
 int /*<<< orphan*/  NGI_CLR_HOOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGI_SET_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RETADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/ * ng_ID2noderef (int /*<<< orphan*/ ) ; 

int
ng_address_ID(node_p here, item_p item, ng_ID_t ID, ng_ID_t retaddr)
{
	node_p dest;

	ITEM_DEBUG_CHECKS;
	/*
	 * Find the target node.
	 */
	dest = ng_ID2noderef(ID); /* GETS REFERENCE! */
	if (dest == NULL) {
		NG_FREE_ITEM(item);
		TRAP_ERROR();
		return(EINVAL);
	}
	/* Fill out the contents */
	NGI_SET_NODE(item, dest);
	NGI_CLR_HOOK(item);
	SET_RETADDR(item, here, retaddr);
	return (0);
}
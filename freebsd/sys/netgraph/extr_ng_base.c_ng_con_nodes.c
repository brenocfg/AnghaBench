#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  TYPE_1__* hook_p ;
struct TYPE_9__ {int hk_refs; int /*<<< orphan*/ * hk_node; struct TYPE_9__* hk_peer; int /*<<< orphan*/  hk_flags; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HK_INVALID ; 
 int /*<<< orphan*/  NG_ALLOC_HOOK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_NAME (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_HOOK_REF (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NOFLAGS ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int ng_add_hook (int /*<<< orphan*/ ,char const*,TYPE_1__**) ; 
 int /*<<< orphan*/  ng_con_part2 ; 
 int /*<<< orphan*/  ng_deadnode ; 
 int /*<<< orphan*/  ng_destroy_hook (TYPE_1__*) ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ ,char const*) ; 
 int ng_send_fn2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_con_nodes(item_p item, node_p node, const char *name,
    node_p node2, const char *name2)
{
	int	error;
	hook_p	hook;
	hook_p	hook2;

	if (ng_findhook(node2, name2) != NULL) {
		return(EEXIST);
	}
	if ((error = ng_add_hook(node, name, &hook)))  /* gives us a ref */
		return (error);
	/* Allocate the other hook and link it up */
	NG_ALLOC_HOOK(hook2);
	if (hook2 == NULL) {
		TRAP_ERROR();
		ng_destroy_hook(hook);	/* XXX check ref counts so far */
		NG_HOOK_UNREF(hook);	/* including our ref */
		return (ENOMEM);
	}
	hook2->hk_refs = 1;		/* start with a reference for us. */
	hook2->hk_flags = HK_INVALID;
	hook2->hk_peer = hook;		/* Link the two together */
	hook->hk_peer = hook2;	
	NG_HOOK_REF(hook);		/* Add a ref for the peer to each*/
	NG_HOOK_REF(hook2);
	hook2->hk_node = &ng_deadnode;
	strlcpy(NG_HOOK_NAME(hook2), name2, NG_HOOKSIZ);

	/*
	 * Queue the function above.
	 * Procesing continues in that function in the lock context of
	 * the other node.
	 */
	if ((error = ng_send_fn2(node2, hook2, item, &ng_con_part2, NULL, 0,
	    NG_NOFLAGS))) {
		printf("failed in ng_con_nodes(): %d\n", error);
		ng_destroy_hook(hook);	/* also zaps peer */
	}

	NG_HOOK_UNREF(hook);		/* Let each hook go if it wants to */
	NG_HOOK_UNREF(hook2);
	return (error);
}
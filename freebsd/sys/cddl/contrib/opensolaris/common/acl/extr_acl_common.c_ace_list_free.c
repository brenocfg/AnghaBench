#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  group; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ acevals_t ;
typedef  TYPE_1__ ace_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  cacl_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
ace_list_free(ace_list_t *al)
{
	acevals_t *node;
	void *cookie;

	if (al == NULL)
		return;

	cookie = NULL;
	while ((node = avl_destroy_nodes(&al->user, &cookie)) != NULL)
		cacl_free(node, sizeof (acevals_t));
	cookie = NULL;
	while ((node = avl_destroy_nodes(&al->group, &cookie)) != NULL)
		cacl_free(node, sizeof (acevals_t));

	avl_destroy(&al->user);
	avl_destroy(&al->group);

	/* free the container itself */
	cacl_free(al, sizeof (ace_list_t));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ypmatch_ent* valdat_val; } ;
struct TYPE_3__ {struct ypmatch_ent* keydat_val; } ;
struct ypmatch_ent {TYPE_2__ ypc_val; TYPE_1__ ypc_key; struct ypmatch_ent* ypc_map; int /*<<< orphan*/  ypc_next; } ;
struct dom_binding {int /*<<< orphan*/  ypmatch_cachecnt; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ypmatch_ent*) ; 

__attribute__((used)) static void
ypmatch_cache_delete(struct dom_binding *ypdb, struct ypmatch_ent *prev,
    struct ypmatch_ent *cur)
{
	if (prev == NULL)
		ypdb->cache = cur->ypc_next;
	else
		prev->ypc_next = cur->ypc_next;

	free(cur->ypc_map);
	free(cur->ypc_key.keydat_val);
	free(cur->ypc_val.valdat_val);
	free(cur);

	ypdb->ypmatch_cachecnt--;

	return;
}
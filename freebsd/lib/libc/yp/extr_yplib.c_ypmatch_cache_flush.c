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
struct ypmatch_ent {struct ypmatch_ent* ypc_next; } ;
struct dom_binding {struct ypmatch_ent* cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ypmatch_cache_delete (struct dom_binding*,int /*<<< orphan*/ *,struct ypmatch_ent*) ; 

__attribute__((used)) static void
ypmatch_cache_flush(struct dom_binding *ypdb)
{
	struct ypmatch_ent	*n, *c = ypdb->cache;

	while (c != NULL) {
		n = c->ypc_next;
		ypmatch_cache_delete(ypdb, NULL, c);
		c = n;
	}

	return;
}
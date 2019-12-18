#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int valdat_len; int /*<<< orphan*/  valdat_val; } ;
typedef  TYPE_3__ valdat ;
typedef  scalar_t__ time_t ;
struct TYPE_8__ {int valdat_len; struct ypmatch_ent* valdat_val; } ;
struct TYPE_7__ {int keydat_len; struct ypmatch_ent* keydat_val; } ;
struct ypmatch_ent {struct ypmatch_ent* ypc_next; TYPE_2__ ypc_val; TYPE_1__ ypc_key; scalar_t__ ypc_expire_t; struct ypmatch_ent* ypc_map; } ;
struct dom_binding {scalar_t__ ypmatch_cachecnt; struct ypmatch_ent* cache; } ;
struct TYPE_10__ {int keydat_len; int /*<<< orphan*/  keydat_val; } ;
typedef  TYPE_4__ keydat ;

/* Variables and functions */
 scalar_t__ YPLIB_EXPIRE ; 
 scalar_t__ YPLIB_MAXCACHE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct ypmatch_ent*,int) ; 
 int /*<<< orphan*/  free (struct ypmatch_ent*) ; 
 void* malloc (int) ; 
 struct ypmatch_ent* strdup (char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ypmatch_cache_expire (struct dom_binding*) ; 

__attribute__((used)) static void
ypmatch_cache_insert(struct dom_binding *ypdb, char *map, keydat *key,
    valdat *val)
{
	struct ypmatch_ent	*new;

	/* Do an expire run to maybe open up a slot. */
	if (ypdb->ypmatch_cachecnt)
		ypmatch_cache_expire(ypdb);

	/*
	 * If there are no slots free, then force an expire of
	 * the least recently used entry.
 	 */
	if (ypdb->ypmatch_cachecnt >= YPLIB_MAXCACHE) {
		struct ypmatch_ent	*o = NULL, *c = ypdb->cache;
		time_t			oldest = 0;

		oldest = ~oldest;

		while (c != NULL) {
			if (c->ypc_expire_t < oldest) {
				oldest = c->ypc_expire_t;
				o = c;
			}
			c = c->ypc_next;
		}

		if (o == NULL)
			return;
		o->ypc_expire_t = 0;
		ypmatch_cache_expire(ypdb);
	}

	new = malloc(sizeof(struct ypmatch_ent));
	if (new == NULL)
		return;

	new->ypc_map = strdup(map);
	if (new->ypc_map == NULL) {
		free(new);
		return;
	}
	new->ypc_key.keydat_val = malloc(key->keydat_len);
	if (new->ypc_key.keydat_val == NULL) {
		free(new->ypc_map);
		free(new);
		return;
	}
	new->ypc_val.valdat_val = malloc(val->valdat_len);
	if (new->ypc_val.valdat_val == NULL) {
		free(new->ypc_val.valdat_val);
		free(new->ypc_map);
		free(new);
		return;
	}

	new->ypc_expire_t = time(NULL) + YPLIB_EXPIRE;
	new->ypc_key.keydat_len = key->keydat_len;
	new->ypc_val.valdat_len = val->valdat_len;
	bcopy(key->keydat_val, new->ypc_key.keydat_val, key->keydat_len);
	bcopy(val->valdat_val, new->ypc_val.valdat_val, val->valdat_len);

	new->ypc_next = ypdb->cache;
	ypdb->cache = new;

	ypdb->ypmatch_cachecnt++;

	return;
}
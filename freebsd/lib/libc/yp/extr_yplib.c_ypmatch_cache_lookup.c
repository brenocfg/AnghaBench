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
struct TYPE_9__ {int /*<<< orphan*/  valdat_val; int /*<<< orphan*/  valdat_len; } ;
typedef  TYPE_3__ valdat ;
struct TYPE_8__ {int /*<<< orphan*/  valdat_val; int /*<<< orphan*/  valdat_len; } ;
struct TYPE_7__ {scalar_t__ keydat_len; int /*<<< orphan*/  keydat_val; } ;
struct ypmatch_ent {TYPE_2__ ypc_val; TYPE_1__ ypc_key; int /*<<< orphan*/  ypc_map; struct ypmatch_ent* ypc_next; } ;
struct dom_binding {struct ypmatch_ent* cache; } ;
struct TYPE_10__ {scalar_t__ keydat_len; int /*<<< orphan*/  keydat_val; } ;
typedef  TYPE_4__ keydat ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ypmatch_cache_expire (struct dom_binding*) ; 

__attribute__((used)) static bool_t
ypmatch_cache_lookup(struct dom_binding *ypdb, char *map, keydat *key,
    valdat *val)
{
	struct ypmatch_ent	*c;

	ypmatch_cache_expire(ypdb);

	for (c = ypdb->cache; c != NULL; c = c->ypc_next) {
		if (strcmp(map, c->ypc_map))
			continue;
		if (key->keydat_len != c->ypc_key.keydat_len)
			continue;
		if (bcmp(key->keydat_val, c->ypc_key.keydat_val,
				key->keydat_len))
			continue;
	}

	if (c == NULL)
		return(FALSE);

	val->valdat_len = c->ypc_val.valdat_len;
	val->valdat_val = c->ypc_val.valdat_val;

	return(TRUE);
}
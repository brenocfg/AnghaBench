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
struct g_raid_tr_class {int /*<<< orphan*/  trc_priority; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct g_raid_tr_class* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct g_raid_tr_class*,struct g_raid_tr_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_raid_tr_class*,int /*<<< orphan*/ ) ; 
 struct g_raid_tr_class* LIST_NEXT (struct g_raid_tr_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_raid_tr_class*,int /*<<< orphan*/ ) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  g_raid_tr_classes ; 
 int /*<<< orphan*/  trc_list ; 

int
g_raid_tr_modevent(module_t mod, int type, void *arg)
{
	struct g_raid_tr_class *class, *c, *nc;
	int error;

	error = 0;
	class = arg;
	switch (type) {
	case MOD_LOAD:
		c = LIST_FIRST(&g_raid_tr_classes);
		if (c == NULL || c->trc_priority > class->trc_priority)
			LIST_INSERT_HEAD(&g_raid_tr_classes, class, trc_list);
		else {
			while ((nc = LIST_NEXT(c, trc_list)) != NULL &&
			    nc->trc_priority < class->trc_priority)
				c = nc;
			LIST_INSERT_AFTER(c, class, trc_list);
		}
		break;
	case MOD_UNLOAD:
		LIST_REMOVE(class, trc_list);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}
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
struct g_hh00 {int post; int error; struct g_class* mp; } ;
struct g_class {scalar_t__ version; char* name; int /*<<< orphan*/  geom; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 scalar_t__ G_VERSION ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  g_free (struct g_hh00*) ; 
 int /*<<< orphan*/  g_init () ; 
 int /*<<< orphan*/  g_load_class ; 
 struct g_hh00* g_malloc (int,int) ; 
 int g_post_event (int /*<<< orphan*/ ,struct g_hh00*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,char*) ; 
 int g_unload_class (struct g_class*) ; 
 int g_waitfor_event (int /*<<< orphan*/ ,struct g_hh00*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 

int
g_modevent(module_t mod, int type, void *data)
{
	struct g_hh00 *hh;
	int error;
	static int g_ignition;
	struct g_class *mp;

	mp = data;
	if (mp->version != G_VERSION) {
		printf("GEOM class %s has Wrong version %x\n",
		    mp->name, mp->version);
		return (EINVAL);
	}
	if (!g_ignition) {
		g_ignition++;
		g_init();
	}
	error = EOPNOTSUPP;
	switch (type) {
	case MOD_LOAD:
		g_trace(G_T_TOPOLOGY, "g_modevent(%s, LOAD)", mp->name);
		hh = g_malloc(sizeof *hh, M_WAITOK | M_ZERO);
		hh->mp = mp;
		/*
		 * Once the system is not cold, MOD_LOAD calls will be
		 * from the userland and the g_event thread will be able
		 * to acknowledge their completion.
		 */
		if (cold) {
			hh->post = 1;
			error = g_post_event(g_load_class, hh, M_WAITOK, NULL);
		} else {
			error = g_waitfor_event(g_load_class, hh, M_WAITOK,
			    NULL);
			if (error == 0)
				error = hh->error;
			g_free(hh);
		}
		break;
	case MOD_UNLOAD:
		g_trace(G_T_TOPOLOGY, "g_modevent(%s, UNLOAD)", mp->name);
		error = g_unload_class(mp);
		if (error == 0) {
			KASSERT(LIST_EMPTY(&mp->geom),
			    ("Unloaded class (%s) still has geom", mp->name));
		}
		break;
	}
	return (error);
}
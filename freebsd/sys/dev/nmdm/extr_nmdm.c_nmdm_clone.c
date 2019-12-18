#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct tty {struct cdev* t_dev; } ;
struct TYPE_3__ {struct tty* np_tty; struct TYPE_3__* np_other; int /*<<< orphan*/  np_callout; int /*<<< orphan*/  np_task; struct nmdmsoftc* np_pair; } ;
struct nmdmsoftc {TYPE_1__ ns_part2; TYPE_1__ ns_part1; int /*<<< orphan*/  ns_mtx; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NMDM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TTYMK_CLONING ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nmdmsoftc*,int /*<<< orphan*/ ) ; 
 struct nmdmsoftc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmdm_class ; 
 int /*<<< orphan*/  nmdm_count ; 
 int /*<<< orphan*/  nmdm_task_tty ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 void* tty_alloc_mutex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int tty_makedevf (struct tty*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 

__attribute__((used)) static void
nmdm_clone(void *arg, struct ucred *cred, char *name, int nameen,
    struct cdev **dev)
{
	struct nmdmsoftc *ns;
	struct tty *tp;
	char *end;
	int error;
	char endc;

	if (*dev != NULL)
		return;
	if (strncmp(name, "nmdm", 4) != 0)
		return;
	if (strlen(name) <= strlen("nmdmX"))
		return;

	/* Device name must be "nmdm%s%c", where %c is 'A' or 'B'. */
	end = name + strlen(name) - 1;
	endc = *end;
	if (endc != 'A' && endc != 'B')
		return;

	ns = malloc(sizeof(*ns), M_NMDM, M_WAITOK | M_ZERO);
	mtx_init(&ns->ns_mtx, "nmdm", NULL, MTX_DEF);

	/* Hook the pairs together. */
	ns->ns_part1.np_pair = ns;
	ns->ns_part1.np_other = &ns->ns_part2;
	TASK_INIT(&ns->ns_part1.np_task, 0, nmdm_task_tty, &ns->ns_part1);
	callout_init_mtx(&ns->ns_part1.np_callout, &ns->ns_mtx, 0);

	ns->ns_part2.np_pair = ns;
	ns->ns_part2.np_other = &ns->ns_part1;
	TASK_INIT(&ns->ns_part2.np_task, 0, nmdm_task_tty, &ns->ns_part2);
	callout_init_mtx(&ns->ns_part2.np_callout, &ns->ns_mtx, 0);

	/* Create device nodes. */
	tp = ns->ns_part1.np_tty = tty_alloc_mutex(&nmdm_class, &ns->ns_part1,
	    &ns->ns_mtx);
	*end = 'A';
	error = tty_makedevf(tp, NULL, endc == 'A' ? TTYMK_CLONING : 0,
	    "%s", name);
	if (error) {
		*end = endc;
		mtx_destroy(&ns->ns_mtx);
		free(ns, M_NMDM);
		return;
	}

	tp = ns->ns_part2.np_tty = tty_alloc_mutex(&nmdm_class, &ns->ns_part2,
	    &ns->ns_mtx);
	*end = 'B';
	error = tty_makedevf(tp, NULL, endc == 'B' ? TTYMK_CLONING : 0,
	    "%s", name);
	if (error) {
		*end = endc;
		mtx_lock(&ns->ns_mtx);
		/* see nmdm_free() */
		ns->ns_part1.np_other = NULL;
		atomic_add_int(&nmdm_count, 1);
		tty_rel_gone(ns->ns_part1.np_tty);
		return;
	}

	if (endc == 'A')
		*dev = ns->ns_part1.np_tty->t_dev;
	else
		*dev = ns->ns_part2.np_tty->t_dev;

	*end = endc;
	atomic_add_int(&nmdm_count, 1);
}
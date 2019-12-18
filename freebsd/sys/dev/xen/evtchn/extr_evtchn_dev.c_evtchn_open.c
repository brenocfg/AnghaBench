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
struct thread {int dummy; } ;
struct per_user_data {struct per_user_data* ring; int /*<<< orphan*/  ring_cons_mutex; int /*<<< orphan*/  ring_prod_mutex; int /*<<< orphan*/  bind_mutex; int /*<<< orphan*/  evtchns; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_EVTCHN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int devfs_set_cdevpriv (struct per_user_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtchn_release ; 
 int /*<<< orphan*/  free (struct per_user_data*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
evtchn_open(struct cdev *dev, int flag, int otyp, struct thread *td)
{
	struct per_user_data *u;
	int error;

	u = malloc(sizeof(*u), M_EVTCHN, M_WAITOK | M_ZERO);
	u->ring = malloc(PAGE_SIZE, M_EVTCHN, M_WAITOK | M_ZERO);

	/* Initialize locks */
	mtx_init(&u->bind_mutex, "evtchn_bind_mutex", NULL, MTX_DEF);
	sx_init(&u->ring_cons_mutex, "evtchn_ringc_sx");
	mtx_init(&u->ring_prod_mutex, "evtchn_ringp_mutex", NULL, MTX_DEF);

	/* Initialize red-black tree. */
	RB_INIT(&u->evtchns);

	/* Assign the allocated per_user_data to this open instance. */
	error = devfs_set_cdevpriv(u, evtchn_release);
	if (error != 0) {
		mtx_destroy(&u->bind_mutex);
		mtx_destroy(&u->ring_prod_mutex);
		sx_destroy(&u->ring_cons_mutex);
		free(u->ring, M_EVTCHN);
		free(u, M_EVTCHN);
	}

	return (error);
}
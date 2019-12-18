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
typedef  int /*<<< orphan*/  u_int32_t ;
struct mtx {int dummy; } ;
struct cam_sim {char const* sim_name; int max_tagged_dev_openings; int max_dev_openings; int refcount; int /*<<< orphan*/  callout; int /*<<< orphan*/  flags; struct mtx* mtx; struct cam_devq* devq; scalar_t__ bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/ * sim_dev; int /*<<< orphan*/  path_id; void* softc; int /*<<< orphan*/  sim_poll; int /*<<< orphan*/  sim_action; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  sim_poll_func ;
typedef  int /*<<< orphan*/  sim_action_func ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PATH_ANY ; 
 int /*<<< orphan*/  CAM_SIM_MPSAFE ; 
 struct mtx Giant ; 
 int /*<<< orphan*/  M_CAMSIM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

struct cam_sim *
cam_sim_alloc(sim_action_func sim_action, sim_poll_func sim_poll,
	      const char *sim_name, void *softc, u_int32_t unit,
	      struct mtx *mtx, int max_dev_transactions,
	      int max_tagged_dev_transactions, struct cam_devq *queue)
{
	struct cam_sim *sim;

	sim = (struct cam_sim *)malloc(sizeof(struct cam_sim),
	    M_CAMSIM, M_ZERO | M_NOWAIT);

	if (sim == NULL)
		return (NULL);

	sim->sim_action = sim_action;
	sim->sim_poll = sim_poll;
	sim->sim_name = sim_name;
	sim->softc = softc;
	sim->path_id = CAM_PATH_ANY;
	sim->sim_dev = NULL;	/* set only by cam_sim_alloc_dev */
	sim->unit_number = unit;
	sim->bus_id = 0;	/* set in xpt_bus_register */
	sim->max_tagged_dev_openings = max_tagged_dev_transactions;
	sim->max_dev_openings = max_dev_transactions;
	sim->flags = 0;
	sim->refcount = 1;
	sim->devq = queue;
	sim->mtx = mtx;
	if (mtx == &Giant) {
		sim->flags |= 0;
		callout_init(&sim->callout, 0);
	} else {
		sim->flags |= CAM_SIM_MPSAFE;
		callout_init(&sim->callout, 1);
	}
	return (sim);
}
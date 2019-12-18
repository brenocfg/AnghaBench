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
struct aac_softc {int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_sim_tqh; } ;
struct aac_sim {int InitiatorBusId; int /*<<< orphan*/ * aac_cam; int /*<<< orphan*/ * sim_dev; struct aac_softc* aac_sc; int /*<<< orphan*/  BusType; scalar_t__ BusNumber; int /*<<< orphan*/  TargetsPerBus; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_MAX_CONTAINERS ; 
 int /*<<< orphan*/  CONTAINER_BUS ; 
 int /*<<< orphan*/  M_AACRAIDBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct aac_sim*) ; 
 int /*<<< orphan*/  free (struct aac_sim*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sim_link ; 

__attribute__((used)) static void
aac_container_bus(struct aac_softc *sc)
{
	struct aac_sim *sim;
	device_t child;

	sim =(struct aac_sim *)malloc(sizeof(struct aac_sim),
		M_AACRAIDBUF, M_NOWAIT | M_ZERO);
	if (sim == NULL) {
		device_printf(sc->aac_dev,
	    	"No memory to add container bus\n");
		panic("Out of memory?!");
	}
	child = device_add_child(sc->aac_dev, "aacraidp", -1);
	if (child == NULL) {
		device_printf(sc->aac_dev,
	    	"device_add_child failed for container bus\n");
		free(sim, M_AACRAIDBUF);
		panic("Out of memory?!");
	}

	sim->TargetsPerBus = AAC_MAX_CONTAINERS;
	sim->BusNumber = 0;
	sim->BusType = CONTAINER_BUS;
	sim->InitiatorBusId = -1;
	sim->aac_sc = sc;
	sim->sim_dev = child;
	sim->aac_cam = NULL;

	device_set_ivars(child, sim);
	device_set_desc(child, "Container Bus");
	TAILQ_INSERT_TAIL(&sc->aac_sim_tqh, sim, sim_link);
	/*
	device_set_desc(child, aac_describe_code(aac_container_types,
			mir->MntTable[0].VolType));
	*/
	bus_generic_attach(sc->aac_dev);
}
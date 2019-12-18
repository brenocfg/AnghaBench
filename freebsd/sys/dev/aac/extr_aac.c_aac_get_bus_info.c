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
struct aac_vmioctl {int /*<<< orphan*/  IoctlCmd; scalar_t__ ObjId; int /*<<< orphan*/  MethId; int /*<<< orphan*/  ObjType; int /*<<< orphan*/  Command; scalar_t__ param; int /*<<< orphan*/  cmd; } ;
struct aac_vmi_businf_resp {scalar_t__ Status; int /*<<< orphan*/  BusInf; } ;
struct aac_softc {int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_sim_tqh; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  scsi_method_id; } ;
struct aac_sim {int BusNumber; int /*<<< orphan*/ * sim_dev; struct aac_softc* aac_sc; int /*<<< orphan*/  InitiatorBusId; int /*<<< orphan*/  TargetsPerBus; } ;
struct aac_getbusinf {int BusCount; scalar_t__* BusValid; int /*<<< orphan*/ * InitiatorBusId; int /*<<< orphan*/  TargetsPerBus; } ;
struct aac_fib {int /*<<< orphan*/ * data; } ;
struct aac_ctcfg_resp {scalar_t__ Status; int /*<<< orphan*/  param; } ;
struct aac_ctcfg {int /*<<< orphan*/  IoctlCmd; scalar_t__ ObjId; int /*<<< orphan*/  MethId; int /*<<< orphan*/  ObjType; int /*<<< orphan*/  Command; scalar_t__ param; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ AAC_BUS_VALID ; 
 int /*<<< orphan*/  CT_GET_SCSI_METHOD ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int /*<<< orphan*/  FT_DRIVE ; 
 int /*<<< orphan*/  GetBusInfo ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ ST_OK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ContainerConfig ; 
 int /*<<< orphan*/  VM_Ioctl ; 
 int /*<<< orphan*/  aac_alloc_sync_fib (struct aac_softc*,struct aac_fib**) ; 
 int /*<<< orphan*/  aac_release_sync_fib (struct aac_softc*) ; 
 int aac_sync_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_fib*,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct aac_getbusinf*,int) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct aac_vmioctl*,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct aac_sim*) ; 
 int /*<<< orphan*/  free (struct aac_sim*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sim_link ; 

__attribute__((used)) static void
aac_get_bus_info(struct aac_softc *sc)
{
	struct aac_fib *fib;
	struct aac_ctcfg *c_cmd;
	struct aac_ctcfg_resp *c_resp;
	struct aac_vmioctl *vmi;
	struct aac_vmi_businf_resp *vmi_resp;
	struct aac_getbusinf businfo;
	struct aac_sim *caminf;
	device_t child;
	int i, found, error;

	mtx_lock(&sc->aac_io_lock);
	aac_alloc_sync_fib(sc, &fib);
	c_cmd = (struct aac_ctcfg *)&fib->data[0];
	bzero(c_cmd, sizeof(struct aac_ctcfg));

	c_cmd->Command = VM_ContainerConfig;
	c_cmd->cmd = CT_GET_SCSI_METHOD;
	c_cmd->param = 0;

	error = aac_sync_fib(sc, ContainerCommand, 0, fib,
	    sizeof(struct aac_ctcfg));
	if (error) {
		device_printf(sc->aac_dev, "Error %d sending "
		    "VM_ContainerConfig command\n", error);
		aac_release_sync_fib(sc);
		mtx_unlock(&sc->aac_io_lock);
		return;
	}

	c_resp = (struct aac_ctcfg_resp *)&fib->data[0];
	if (c_resp->Status != ST_OK) {
		device_printf(sc->aac_dev, "VM_ContainerConfig returned 0x%x\n",
		    c_resp->Status);
		aac_release_sync_fib(sc);
		mtx_unlock(&sc->aac_io_lock);
		return;
	}

	sc->scsi_method_id = c_resp->param;

	vmi = (struct aac_vmioctl *)&fib->data[0];
	bzero(vmi, sizeof(struct aac_vmioctl));

	vmi->Command = VM_Ioctl;
	vmi->ObjType = FT_DRIVE;
	vmi->MethId = sc->scsi_method_id;
	vmi->ObjId = 0;
	vmi->IoctlCmd = GetBusInfo;

	error = aac_sync_fib(sc, ContainerCommand, 0, fib,
	    sizeof(struct aac_vmi_businf_resp));
	if (error) {
		device_printf(sc->aac_dev, "Error %d sending VMIoctl command\n",
		    error);
		aac_release_sync_fib(sc);
		mtx_unlock(&sc->aac_io_lock);
		return;
	}

	vmi_resp = (struct aac_vmi_businf_resp *)&fib->data[0];
	if (vmi_resp->Status != ST_OK) {
		device_printf(sc->aac_dev, "VM_Ioctl returned %d\n",
		    vmi_resp->Status);
		aac_release_sync_fib(sc);
		mtx_unlock(&sc->aac_io_lock);
		return;
	}

	bcopy(&vmi_resp->BusInf, &businfo, sizeof(struct aac_getbusinf));
	aac_release_sync_fib(sc);
	mtx_unlock(&sc->aac_io_lock);

	found = 0;
	for (i = 0; i < businfo.BusCount; i++) {
		if (businfo.BusValid[i] != AAC_BUS_VALID)
			continue;

		caminf = (struct aac_sim *)malloc( sizeof(struct aac_sim),
		    M_AACBUF, M_NOWAIT | M_ZERO);
		if (caminf == NULL) {
			device_printf(sc->aac_dev,
			    "No memory to add passthrough bus %d\n", i);
			break;
		}

		child = device_add_child(sc->aac_dev, "aacp", -1);
		if (child == NULL) {
			device_printf(sc->aac_dev,
			    "device_add_child failed for passthrough bus %d\n",
			    i);
			free(caminf, M_AACBUF);
			break;
		}

		caminf->TargetsPerBus = businfo.TargetsPerBus;
		caminf->BusNumber = i;
		caminf->InitiatorBusId = businfo.InitiatorBusId[i];
		caminf->aac_sc = sc;
		caminf->sim_dev = child;

		device_set_ivars(child, caminf);
		device_set_desc(child, "SCSI Passthrough Bus");
		TAILQ_INSERT_TAIL(&sc->aac_sim_tqh, caminf, sim_link);

		found = 1;
	}

	if (found)
		bus_generic_attach(sc->aac_dev);
}
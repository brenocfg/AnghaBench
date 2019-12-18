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
struct vmctx {int dummy; } ;
struct TYPE_8__ {int vsp_txq; int vsp_rxq; int vsp_enabled; int /*<<< orphan*/  vsp_cb; struct pci_vtcon_softc* vsp_sc; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vs_mtx; } ;
struct pci_vtcon_softc {TYPE_2__ vsc_control_port; TYPE_3__ vsc_vs; TYPE_4__* vsc_queues; int /*<<< orphan*/  vsc_mtx; TYPE_1__* vsc_config; } ;
struct pci_vtcon_config {int dummy; } ;
struct pci_devinst {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  vq_notify; int /*<<< orphan*/  vq_qsize; } ;
struct TYPE_7__ {int cols; int rows; int /*<<< orphan*/  max_nr_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIC_SIMPLECOMM ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  VIRTIO_DEV_CONSOLE ; 
 int /*<<< orphan*/  VIRTIO_TYPE_CONSOLE ; 
 int /*<<< orphan*/  VIRTIO_VENDOR ; 
 int /*<<< orphan*/  VTCON_MAXPORTS ; 
 int VTCON_MAXQ ; 
 int /*<<< orphan*/  VTCON_RINGSZ ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fbsdrun_virtio_msix () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_vtcon_control_tx ; 
 int /*<<< orphan*/  pci_vtcon_notify_rx ; 
 int /*<<< orphan*/  pci_vtcon_notify_tx ; 
 scalar_t__ pci_vtcon_sock_add (struct pci_vtcon_softc*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ vi_intr_init (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_set_io_bar (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_softc_linkup (TYPE_3__*,int /*<<< orphan*/ *,struct pci_vtcon_softc*,struct pci_devinst*,TYPE_4__*) ; 
 int /*<<< orphan*/  vtcon_vi_consts ; 

__attribute__((used)) static int
pci_vtcon_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	struct pci_vtcon_softc *sc;
	char *portname = NULL;
	char *portpath = NULL;
	char *opt;
	int i;	

	sc = calloc(1, sizeof(struct pci_vtcon_softc));
	sc->vsc_config = calloc(1, sizeof(struct pci_vtcon_config));
	sc->vsc_config->max_nr_ports = VTCON_MAXPORTS;
	sc->vsc_config->cols = 80;
	sc->vsc_config->rows = 25; 

	vi_softc_linkup(&sc->vsc_vs, &vtcon_vi_consts, sc, pi, sc->vsc_queues);
	sc->vsc_vs.vs_mtx = &sc->vsc_mtx;

	for (i = 0; i < VTCON_MAXQ; i++) {
		sc->vsc_queues[i].vq_qsize = VTCON_RINGSZ;
		sc->vsc_queues[i].vq_notify = i % 2 == 0
		    ? pci_vtcon_notify_rx
		    : pci_vtcon_notify_tx;
	}

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, VIRTIO_DEV_CONSOLE);
	pci_set_cfgdata16(pi, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_SIMPLECOMM);
	pci_set_cfgdata16(pi, PCIR_SUBDEV_0, VIRTIO_TYPE_CONSOLE);
	pci_set_cfgdata16(pi, PCIR_SUBVEND_0, VIRTIO_VENDOR);

	if (vi_intr_init(&sc->vsc_vs, 1, fbsdrun_virtio_msix()))
		return (1);
	vi_set_io_bar(&sc->vsc_vs, 0);

	/* create control port */
	sc->vsc_control_port.vsp_sc = sc;
	sc->vsc_control_port.vsp_txq = 2;
	sc->vsc_control_port.vsp_rxq = 3;
	sc->vsc_control_port.vsp_cb = pci_vtcon_control_tx;
	sc->vsc_control_port.vsp_enabled = true;

	while ((opt = strsep(&opts, ",")) != NULL) {
		portname = strsep(&opt, "=");
		portpath = opt;

		/* create port */
		if (pci_vtcon_sock_add(sc, portname, portpath) < 0) {
			fprintf(stderr, "cannot create port %s: %s\n",
			    portname, strerror(errno));
			return (1);
		}
	}

	return (0);
}
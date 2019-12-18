#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vs_mtx; } ;
struct pci_vtscsi_softc {scalar_t__ vss_ctl_fd; TYPE_1__ vss_vs; int /*<<< orphan*/ * vss_queues; TYPE_2__* vss_vq; int /*<<< orphan*/  vss_mtx; int /*<<< orphan*/  vss_iid; } ;
struct pci_devinst {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vq_notify; void* vq_qsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIC_STORAGE ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  VIRTIO_DEV_SCSI ; 
 int /*<<< orphan*/  VIRTIO_TYPE_SCSI ; 
 int /*<<< orphan*/  VIRTIO_VENDOR ; 
 int VTSCSI_MAXQ ; 
 void* VTSCSI_RINGSZ ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 struct pci_vtscsi_softc* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fbsdrun_virtio_msix () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct pci_vtscsi_softc*) ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_vtscsi_controlq_notify ; 
 int /*<<< orphan*/  pci_vtscsi_eventq_notify ; 
 int /*<<< orphan*/  pci_vtscsi_init_queue (struct pci_vtscsi_softc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_vtscsi_requestq_notify ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vi_intr_init (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_set_io_bar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_softc_linkup (TYPE_1__*,int /*<<< orphan*/ *,struct pci_vtscsi_softc*,struct pci_devinst*,TYPE_2__*) ; 
 int /*<<< orphan*/  vtscsi_vi_consts ; 

__attribute__((used)) static int
pci_vtscsi_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	struct pci_vtscsi_softc *sc;
	char *opt, *optname;
	const char *devname;
	int i, optidx = 0;

	sc = calloc(1, sizeof(struct pci_vtscsi_softc));
	devname = "/dev/cam/ctl";
	while ((opt = strsep(&opts, ",")) != NULL) {
		optname = strsep(&opt, "=");
		if (opt == NULL && optidx == 0) {
			if (optname[0] != 0)
				devname = optname;
		} else if (strcmp(optname, "dev") == 0 && opt != NULL) {
			devname = opt;
		} else if (strcmp(optname, "iid") == 0 && opt != NULL) {
			sc->vss_iid = strtoul(opt, NULL, 10);
		} else {
			fprintf(stderr, "Invalid option %s\n", optname);
			free(sc);
			return (1);
		}
		optidx++;
	}

	sc->vss_ctl_fd = open(devname, O_RDWR);
	if (sc->vss_ctl_fd < 0) {
		WPRINTF(("cannot open %s: %s\n", devname, strerror(errno)));
		free(sc);
		return (1);
	}

	vi_softc_linkup(&sc->vss_vs, &vtscsi_vi_consts, sc, pi, sc->vss_vq);
	sc->vss_vs.vs_mtx = &sc->vss_mtx;

	/* controlq */
	sc->vss_vq[0].vq_qsize = VTSCSI_RINGSZ;
	sc->vss_vq[0].vq_notify = pci_vtscsi_controlq_notify;

	/* eventq */
	sc->vss_vq[1].vq_qsize = VTSCSI_RINGSZ;
	sc->vss_vq[1].vq_notify = pci_vtscsi_eventq_notify;

	/* request queues */
	for (i = 2; i < VTSCSI_MAXQ; i++) {
		sc->vss_vq[i].vq_qsize = VTSCSI_RINGSZ;
		sc->vss_vq[i].vq_notify = pci_vtscsi_requestq_notify;
		pci_vtscsi_init_queue(sc, &sc->vss_queues[i - 2], i - 2);
	}

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, VIRTIO_DEV_SCSI);
	pci_set_cfgdata16(pi, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_STORAGE);
	pci_set_cfgdata16(pi, PCIR_SUBDEV_0, VIRTIO_TYPE_SCSI);
	pci_set_cfgdata16(pi, PCIR_SUBVEND_0, VIRTIO_VENDOR);

	if (vi_intr_init(&sc->vss_vs, 1, fbsdrun_virtio_msix()))
		return (1);
	vi_set_io_bar(&sc->vss_vs, 0);

	return (0);
}
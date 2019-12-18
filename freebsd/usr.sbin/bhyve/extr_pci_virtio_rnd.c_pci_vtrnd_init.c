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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint8_t ;
struct vmctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vs_mtx; } ;
struct TYPE_6__ {int /*<<< orphan*/  vq_qsize; } ;
struct pci_vtrnd_softc {int vrsc_fd; TYPE_1__ vrsc_vs; TYPE_2__ vrsc_vq; int /*<<< orphan*/  vrsc_mtx; } ;
struct pci_devinst {int dummy; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  PCIC_CRYPTO ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  VIRTIO_DEV_RANDOM ; 
 int /*<<< orphan*/  VIRTIO_TYPE_ENTROPY ; 
 int /*<<< orphan*/  VIRTIO_VENDOR ; 
 int /*<<< orphan*/  VTRND_RINGSZ ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pci_vtrnd_softc* calloc (int,int) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fbsdrun_virtio_msix () ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vi_intr_init (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_set_io_bar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_softc_linkup (TYPE_1__*,int /*<<< orphan*/ *,struct pci_vtrnd_softc*,struct pci_devinst*,TYPE_2__*) ; 
 int /*<<< orphan*/  vtrnd_vi_consts ; 

__attribute__((used)) static int
pci_vtrnd_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	struct pci_vtrnd_softc *sc;
	int fd;
	int len;
	uint8_t v;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
#endif

	/*
	 * Should always be able to open /dev/random.
	 */
	fd = open("/dev/random", O_RDONLY | O_NONBLOCK);

	assert(fd >= 0);

#ifndef WITHOUT_CAPSICUM
	cap_rights_init(&rights, CAP_READ);
	if (caph_rights_limit(fd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	/*
	 * Check that device is seeded and non-blocking.
	 */
	len = read(fd, &v, sizeof(v));
	if (len <= 0) {
		WPRINTF(("vtrnd: /dev/random not ready, read(): %d", len));
		close(fd);
		return (1);
	}

	sc = calloc(1, sizeof(struct pci_vtrnd_softc));

	vi_softc_linkup(&sc->vrsc_vs, &vtrnd_vi_consts, sc, pi, &sc->vrsc_vq);
	sc->vrsc_vs.vs_mtx = &sc->vrsc_mtx;

	sc->vrsc_vq.vq_qsize = VTRND_RINGSZ;

	/* keep /dev/random opened while emulating */
	sc->vrsc_fd = fd;

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, VIRTIO_DEV_RANDOM);
	pci_set_cfgdata16(pi, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_CRYPTO);
	pci_set_cfgdata16(pi, PCIR_SUBDEV_0, VIRTIO_TYPE_ENTROPY);
	pci_set_cfgdata16(pi, PCIR_SUBVEND_0, VIRTIO_VENDOR);

	if (vi_intr_init(&sc->vrsc_vs, 1, fbsdrun_virtio_msix()))
		return (1);
	vi_set_io_bar(&sc->vrsc_vs, 0);

	return (0);
}
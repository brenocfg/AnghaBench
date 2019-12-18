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
struct vmctx {int dummy; } ;
struct pci_devinst {struct passthru_softc* pi_arg; } ;
struct passthru_softc {struct pci_devinst* psc_pi; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  cap_ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_MMAP_RW ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IODEV_PIO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIOCGETBAR ; 
 int /*<<< orphan*/  PCIOCREAD ; 
 int /*<<< orphan*/  PCIOCWRITE ; 
 int VM_MEM_F_WIRED ; 
 int /*<<< orphan*/  _PATH_DEVIO ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  _PATH_MEM ; 
 struct passthru_softc* calloc (int,int) ; 
 int /*<<< orphan*/  cap_rights_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int caph_ioctls_limit (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int caph_rights_limit (scalar_t__,int /*<<< orphan*/ *) ; 
 int cfginit (struct vmctx*,struct pci_devinst*,int,int,int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct passthru_softc*) ; 
 scalar_t__ iofd ; 
 scalar_t__ memfd ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ *) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pcifd ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 scalar_t__ vm_assign_pptdev (struct vmctx*,int,int,int) ; 
 int vm_get_memflags (struct vmctx*) ; 
 int /*<<< orphan*/  vm_unassign_pptdev (struct vmctx*,int,int,int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
passthru_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	int bus, slot, func, error, memflags;
	struct passthru_softc *sc;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
	cap_ioctl_t pci_ioctls[] = { PCIOCREAD, PCIOCWRITE, PCIOCGETBAR };
	cap_ioctl_t io_ioctls[] = { IODEV_PIO };
#endif

	sc = NULL;
	error = 1;

#ifndef WITHOUT_CAPSICUM
	cap_rights_init(&rights, CAP_IOCTL, CAP_READ, CAP_WRITE);
#endif

	memflags = vm_get_memflags(ctx);
	if (!(memflags & VM_MEM_F_WIRED)) {
		warnx("passthru requires guest memory to be wired");
		return (error);
	}

	if (pcifd < 0) {
		pcifd = open(_PATH_DEVPCI, O_RDWR, 0);
		if (pcifd < 0) {
			warn("failed to open %s", _PATH_DEVPCI);
			return (error);
		}
	}

#ifndef WITHOUT_CAPSICUM
	if (caph_rights_limit(pcifd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
	if (caph_ioctls_limit(pcifd, pci_ioctls, nitems(pci_ioctls)) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	if (iofd < 0) {
		iofd = open(_PATH_DEVIO, O_RDWR, 0);
		if (iofd < 0) {
			warn("failed to open %s", _PATH_DEVIO);
			return (error);
		}
	}

#ifndef WITHOUT_CAPSICUM
	if (caph_rights_limit(iofd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
	if (caph_ioctls_limit(iofd, io_ioctls, nitems(io_ioctls)) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	if (memfd < 0) {
		memfd = open(_PATH_MEM, O_RDWR, 0);
		if (memfd < 0) {
			warn("failed to open %s", _PATH_MEM);
			return (error);
		}
	}

#ifndef WITHOUT_CAPSICUM
	cap_rights_clear(&rights, CAP_IOCTL);
	cap_rights_set(&rights, CAP_MMAP_RW);
	if (caph_rights_limit(memfd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	if (opts == NULL ||
	    sscanf(opts, "%d/%d/%d", &bus, &slot, &func) != 3) {
		warnx("invalid passthru options");
		return (error);
	}

	if (vm_assign_pptdev(ctx, bus, slot, func) != 0) {
		warnx("PCI device at %d/%d/%d is not using the ppt(4) driver",
		    bus, slot, func);
		goto done;
	}

	sc = calloc(1, sizeof(struct passthru_softc));

	pi->pi_arg = sc;
	sc->psc_pi = pi;

	/* initialize config space */
	error = cfginit(ctx, pi, bus, slot, func);
done:
	if (error) {
		free(sc);
		vm_unassign_pptdev(ctx, bus, slot, func);
	}
	return (error);
}
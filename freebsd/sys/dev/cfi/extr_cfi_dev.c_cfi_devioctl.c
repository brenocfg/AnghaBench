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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct thread {int dummy; } ;
struct cfiocqry {int offset; int count; int /*<<< orphan*/  buffer; } ;
struct cfi_softc {int sc_size; int sc_width; int /*<<< orphan*/  sc_writing; } ;
struct cdev {struct cfi_softc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CFIOCGFACTORYPR 133 
#define  CFIOCGOEMPR 132 
#define  CFIOCGPLR 131 
#define  CFIOCQRY 130 
#define  CFIOCSOEMPR 129 
#define  CFIOCSPLR 128 
 int ENOIOCTL ; 
 int ENOSPC ; 
 int ESPIPE ; 
 int cfi_block_finish (struct cfi_softc*) ; 
 int cfi_intel_get_factory_pr (struct cfi_softc*,int /*<<< orphan*/ *) ; 
 int cfi_intel_get_oem_pr (struct cfi_softc*,int /*<<< orphan*/ *) ; 
 int cfi_intel_get_plr (struct cfi_softc*,int /*<<< orphan*/ *) ; 
 int cfi_intel_set_oem_pr (struct cfi_softc*,int /*<<< orphan*/ ) ; 
 int cfi_intel_set_plr (struct cfi_softc*) ; 
 int /*<<< orphan*/  cfi_read_qry (struct cfi_softc*,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cfi_devioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct cfi_softc *sc;
	struct cfiocqry *rq;
	int error;
	u_char val;

	sc = dev->si_drv1;
	error = 0;

	switch (cmd) {
	case CFIOCQRY:
		if (sc->sc_writing) {
			error = cfi_block_finish(sc);
			if (error)
				break;
		}
		rq = (struct cfiocqry *)data;
		if (rq->offset >= sc->sc_size / sc->sc_width)
			return (ESPIPE);
		if (rq->offset + rq->count > sc->sc_size / sc->sc_width)
			return (ENOSPC);

		while (!error && rq->count--) {
			val = cfi_read_qry(sc, rq->offset++);
			error = copyout(&val, rq->buffer++, 1);
		}
		break;
#ifdef CFI_SUPPORT_STRATAFLASH
	case CFIOCGFACTORYPR:
		error = cfi_intel_get_factory_pr(sc, (uint64_t *)data);
		break;
	case CFIOCGOEMPR:
		error = cfi_intel_get_oem_pr(sc, (uint64_t *)data);
		break;
	case CFIOCSOEMPR:
		error = cfi_intel_set_oem_pr(sc, *(uint64_t *)data);
		break;
	case CFIOCGPLR:
		error = cfi_intel_get_plr(sc, (uint32_t *)data);
		break;
	case CFIOCSPLR:
		error = cfi_intel_set_plr(sc);
		break;
#endif /* CFI_SUPPORT_STRATAFLASH */
	default:
		error = ENOIOCTL;
		break;
	}
	return (error);
}
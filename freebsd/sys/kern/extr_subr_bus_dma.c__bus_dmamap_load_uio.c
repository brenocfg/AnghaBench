#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uio {scalar_t__ uio_segflg; scalar_t__ uio_resid; int uio_iovcnt; struct iovec* uio_iov; TYPE_2__* uio_td; } ;
struct iovec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_4__ {TYPE_1__* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UIO_USERSPACE ; 
 int _bus_dmamap_load_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_bus_dmamap_load_uio(bus_dma_tag_t dmat, bus_dmamap_t map, struct uio *uio,
    int *nsegs, int flags)
{
	bus_size_t resid;
	bus_size_t minlen;
	struct iovec *iov;
	pmap_t pmap;
	caddr_t addr;
	int error, i;

	if (uio->uio_segflg == UIO_USERSPACE) {
		KASSERT(uio->uio_td != NULL,
			("bus_dmamap_load_uio: USERSPACE but no proc"));
		pmap = vmspace_pmap(uio->uio_td->td_proc->p_vmspace);
	} else
		pmap = kernel_pmap;
	resid = uio->uio_resid;
	iov = uio->uio_iov;
	error = 0;

	for (i = 0; i < uio->uio_iovcnt && resid != 0 && !error; i++) {
		/*
		 * Now at the first iovec to load.  Load each iovec
		 * until we have exhausted the residual count.
		 */

		addr = (caddr_t) iov[i].iov_base;
		minlen = resid < iov[i].iov_len ? resid : iov[i].iov_len;
		if (minlen > 0) {
			error = _bus_dmamap_load_buffer(dmat, map, addr,
			    minlen, pmap, flags, NULL, nsegs);
			resid -= minlen;
		}
	}

	return (error);
}
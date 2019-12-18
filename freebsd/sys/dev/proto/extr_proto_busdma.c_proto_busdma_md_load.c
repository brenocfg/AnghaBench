#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uio {int uio_iovcnt; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_resid; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct thread {TYPE_1__* td_proc; } ;
struct proto_md {int /*<<< orphan*/  physaddr; int /*<<< orphan*/  bd_map; int /*<<< orphan*/  bd_tag; } ;
struct TYPE_5__ {int phys_nsegs; int /*<<< orphan*/  phys_addr; scalar_t__ virt_addr; int /*<<< orphan*/  virt_size; } ;
struct TYPE_6__ {TYPE_2__ md; } ;
struct proto_ioc_busdma {TYPE_3__ u; } ;
struct proto_callback_bundle {struct proto_ioc_busdma* ioc; struct proto_md* md; struct proto_busdma* busdma; } ;
struct proto_busdma {int dummy; } ;
struct iovec {int /*<<< orphan*/  iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int bus_dmamap_load_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,struct proto_callback_bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_extract (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  proto_busdma_md_load_callback ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_busdma_md_load(struct proto_busdma *busdma, struct proto_md *md,
    struct proto_ioc_busdma *ioc, struct thread *td)
{
	struct proto_callback_bundle pcb;
	struct iovec iov;
	struct uio uio;
	pmap_t pmap;
	int error;

	iov.iov_base = (void *)(uintptr_t)ioc->u.md.virt_addr;
	iov.iov_len = ioc->u.md.virt_size;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = 0;
	uio.uio_resid = iov.iov_len;
	uio.uio_segflg = UIO_USERSPACE;
	uio.uio_rw = UIO_READ;
	uio.uio_td = td;

	pcb.busdma = busdma;
	pcb.md = md;
	pcb.ioc = ioc;
	error = bus_dmamap_load_uio(md->bd_tag, md->bd_map, &uio,
	    proto_busdma_md_load_callback, &pcb, BUS_DMA_NOWAIT);
	if (error)
		return (error);

	/* XXX determine *all* physical memory segments */
	pmap = vmspace_pmap(td->td_proc->p_vmspace);
	md->physaddr = pmap_extract(pmap, ioc->u.md.virt_addr);
	ioc->u.md.phys_nsegs = 1;	/* XXX */
	ioc->u.md.phys_addr = md->physaddr;
	return (0);
}
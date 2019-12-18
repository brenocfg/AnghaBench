#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct vmctx {int dummy; } ;
struct virtio_softc {int vs_flags; int vs_negotiated_caps; size_t vs_curq; int vs_status; int vs_isr; int vs_msix_cfg_idx; scalar_t__ vs_mtx; TYPE_1__* vs_queues; struct virtio_consts* vs_vc; } ;
struct virtio_consts {char* vc_name; int vc_cfgsize; int (* vc_cfgread ) (int /*<<< orphan*/ ,int,int,int*) ;int vc_hv_caps; size_t vc_nvq; } ;
struct pci_devinst {struct virtio_softc* pi_arg; } ;
struct config_reg {int cr_size; char* cr_name; } ;
struct TYPE_2__ {int vq_pfn; int vq_qsize; int vq_msix_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_SOFTC (struct virtio_softc*) ; 
 int VIRTIO_MSI_NO_VECTOR ; 
 int VIRTIO_USE_MSIX ; 
 scalar_t__ VTCFG_R_CFG0 ; 
 scalar_t__ VTCFG_R_CFG1 ; 
#define  VTCFG_R_CFGVEC 137 
#define  VTCFG_R_GUESTCAP 136 
#define  VTCFG_R_HOSTCAP 135 
#define  VTCFG_R_ISR 134 
#define  VTCFG_R_PFN 133 
#define  VTCFG_R_QNOTIFY 132 
#define  VTCFG_R_QNUM 131 
#define  VTCFG_R_QSEL 130 
#define  VTCFG_R_QVEC 129 
#define  VTCFG_R_STATUS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,int) ; 
 scalar_t__ pci_emul_msix_tread (struct pci_devinst*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_lintr_deassert (struct pci_devinst*) ; 
 scalar_t__ pci_msix_enabled (struct pci_devinst*) ; 
 int pci_msix_pba_bar (struct pci_devinst*) ; 
 int pci_msix_table_bar (struct pci_devinst*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ ,int,int,int*) ; 
 struct config_reg* vi_find_cr (scalar_t__) ; 

uint64_t
vi_pci_read(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
	    int baridx, uint64_t offset, int size)
{
	struct virtio_softc *vs = pi->pi_arg;
	struct virtio_consts *vc;
	struct config_reg *cr;
	uint64_t virtio_config_size, max;
	const char *name;
	uint32_t newoff;
	uint32_t value;
	int error;

	if (vs->vs_flags & VIRTIO_USE_MSIX) {
		if (baridx == pci_msix_table_bar(pi) ||
		    baridx == pci_msix_pba_bar(pi)) {
			return (pci_emul_msix_tread(pi, offset, size));
		}
	}

	/* XXX probably should do something better than just assert() */
	assert(baridx == 0);

	if (vs->vs_mtx)
		pthread_mutex_lock(vs->vs_mtx);

	vc = vs->vs_vc;
	name = vc->vc_name;
	value = size == 1 ? 0xff : size == 2 ? 0xffff : 0xffffffff;

	if (size != 1 && size != 2 && size != 4)
		goto bad;

	if (pci_msix_enabled(pi))
		virtio_config_size = VTCFG_R_CFG1;
	else
		virtio_config_size = VTCFG_R_CFG0;

	if (offset >= virtio_config_size) {
		/*
		 * Subtract off the standard size (including MSI-X
		 * registers if enabled) and dispatch to underlying driver.
		 * If that fails, fall into general code.
		 */
		newoff = offset - virtio_config_size;
		max = vc->vc_cfgsize ? vc->vc_cfgsize : 0x100000000;
		if (newoff + size > max)
			goto bad;
		error = (*vc->vc_cfgread)(DEV_SOFTC(vs), newoff, size, &value);
		if (!error)
			goto done;
	}

bad:
	cr = vi_find_cr(offset);
	if (cr == NULL || cr->cr_size != size) {
		if (cr != NULL) {
			/* offset must be OK, so size must be bad */
			fprintf(stderr,
			    "%s: read from %s: bad size %d\r\n",
			    name, cr->cr_name, size);
		} else {
			fprintf(stderr,
			    "%s: read from bad offset/size %jd/%d\r\n",
			    name, (uintmax_t)offset, size);
		}
		goto done;
	}

	switch (offset) {
	case VTCFG_R_HOSTCAP:
		value = vc->vc_hv_caps;
		break;
	case VTCFG_R_GUESTCAP:
		value = vs->vs_negotiated_caps;
		break;
	case VTCFG_R_PFN:
		if (vs->vs_curq < vc->vc_nvq)
			value = vs->vs_queues[vs->vs_curq].vq_pfn;
		break;
	case VTCFG_R_QNUM:
		value = vs->vs_curq < vc->vc_nvq ?
		    vs->vs_queues[vs->vs_curq].vq_qsize : 0;
		break;
	case VTCFG_R_QSEL:
		value = vs->vs_curq;
		break;
	case VTCFG_R_QNOTIFY:
		value = 0;	/* XXX */
		break;
	case VTCFG_R_STATUS:
		value = vs->vs_status;
		break;
	case VTCFG_R_ISR:
		value = vs->vs_isr;
		vs->vs_isr = 0;		/* a read clears this flag */
		if (value)
			pci_lintr_deassert(pi);
		break;
	case VTCFG_R_CFGVEC:
		value = vs->vs_msix_cfg_idx;
		break;
	case VTCFG_R_QVEC:
		value = vs->vs_curq < vc->vc_nvq ?
		    vs->vs_queues[vs->vs_curq].vq_msix_idx :
		    VIRTIO_MSI_NO_VECTOR;
		break;
	}
done:
	if (vs->vs_mtx)
		pthread_mutex_unlock(vs->vs_mtx);
	return (value);
}
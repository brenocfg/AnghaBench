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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct vqueue_info {scalar_t__ vq_msix_idx; int /*<<< orphan*/  (* vq_notify ) (int /*<<< orphan*/ ,struct vqueue_info*) ;} ;
struct vmctx {int dummy; } ;
struct virtio_softc {int vs_flags; scalar_t__ vs_curq; scalar_t__ vs_mtx; struct vqueue_info* vs_queues; scalar_t__ vs_msix_cfg_idx; scalar_t__ vs_status; scalar_t__ vs_negotiated_caps; struct virtio_consts* vs_vc; } ;
struct virtio_consts {char* vc_name; int vc_cfgsize; int (* vc_cfgwrite ) (int /*<<< orphan*/ ,int,int,scalar_t__) ;scalar_t__ vc_hv_caps; scalar_t__ vc_nvq; int /*<<< orphan*/  (* vc_reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* vc_qnotify ) (int /*<<< orphan*/ ,struct vqueue_info*) ;int /*<<< orphan*/  (* vc_apply_features ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct pci_devinst {struct virtio_softc* pi_arg; } ;
struct config_reg {int cr_size; char* cr_name; scalar_t__ cr_ro; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_SOFTC (struct virtio_softc*) ; 
 int VIRTIO_USE_MSIX ; 
 scalar_t__ VTCFG_R_CFG0 ; 
 scalar_t__ VTCFG_R_CFG1 ; 
#define  VTCFG_R_CFGVEC 134 
#define  VTCFG_R_GUESTCAP 133 
#define  VTCFG_R_PFN 132 
#define  VTCFG_R_QNOTIFY 131 
#define  VTCFG_R_QSEL 130 
#define  VTCFG_R_QVEC 129 
#define  VTCFG_R_STATUS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  pci_emul_msix_twrite (struct pci_devinst*,scalar_t__,int,scalar_t__) ; 
 scalar_t__ pci_msix_enabled (struct pci_devinst*) ; 
 int pci_msix_pba_bar (struct pci_devinst*) ; 
 int pci_msix_table_bar (struct pci_devinst*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct vqueue_info*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct vqueue_info*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 struct config_reg* vi_find_cr (scalar_t__) ; 
 int /*<<< orphan*/  vi_vq_init (struct virtio_softc*,scalar_t__) ; 

void
vi_pci_write(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
	     int baridx, uint64_t offset, int size, uint64_t value)
{
	struct virtio_softc *vs = pi->pi_arg;
	struct vqueue_info *vq;
	struct virtio_consts *vc;
	struct config_reg *cr;
	uint64_t virtio_config_size, max;
	const char *name;
	uint32_t newoff;
	int error;

	if (vs->vs_flags & VIRTIO_USE_MSIX) {
		if (baridx == pci_msix_table_bar(pi) ||
		    baridx == pci_msix_pba_bar(pi)) {
			pci_emul_msix_twrite(pi, offset, size, value);
			return;
		}
	}

	/* XXX probably should do something better than just assert() */
	assert(baridx == 0);

	if (vs->vs_mtx)
		pthread_mutex_lock(vs->vs_mtx);

	vc = vs->vs_vc;
	name = vc->vc_name;

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
		 */
		newoff = offset - virtio_config_size;
		max = vc->vc_cfgsize ? vc->vc_cfgsize : 0x100000000;
		if (newoff + size > max)
			goto bad;
		error = (*vc->vc_cfgwrite)(DEV_SOFTC(vs), newoff, size, value);
		if (!error)
			goto done;
	}

bad:
	cr = vi_find_cr(offset);
	if (cr == NULL || cr->cr_size != size || cr->cr_ro) {
		if (cr != NULL) {
			/* offset must be OK, wrong size and/or reg is R/O */
			if (cr->cr_size != size)
				fprintf(stderr,
				    "%s: write to %s: bad size %d\r\n",
				    name, cr->cr_name, size);
			if (cr->cr_ro)
				fprintf(stderr,
				    "%s: write to read-only reg %s\r\n",
				    name, cr->cr_name);
		} else {
			fprintf(stderr,
			    "%s: write to bad offset/size %jd/%d\r\n",
			    name, (uintmax_t)offset, size);
		}
		goto done;
	}

	switch (offset) {
	case VTCFG_R_GUESTCAP:
		vs->vs_negotiated_caps = value & vc->vc_hv_caps;
		if (vc->vc_apply_features)
			(*vc->vc_apply_features)(DEV_SOFTC(vs),
			    vs->vs_negotiated_caps);
		break;
	case VTCFG_R_PFN:
		if (vs->vs_curq >= vc->vc_nvq)
			goto bad_qindex;
		vi_vq_init(vs, value);
		break;
	case VTCFG_R_QSEL:
		/*
		 * Note that the guest is allowed to select an
		 * invalid queue; we just need to return a QNUM
		 * of 0 while the bad queue is selected.
		 */
		vs->vs_curq = value;
		break;
	case VTCFG_R_QNOTIFY:
		if (value >= vc->vc_nvq) {
			fprintf(stderr, "%s: queue %d notify out of range\r\n",
				name, (int)value);
			goto done;
		}
		vq = &vs->vs_queues[value];
		if (vq->vq_notify)
			(*vq->vq_notify)(DEV_SOFTC(vs), vq);
		else if (vc->vc_qnotify)
			(*vc->vc_qnotify)(DEV_SOFTC(vs), vq);
		else
			fprintf(stderr,
			    "%s: qnotify queue %d: missing vq/vc notify\r\n",
				name, (int)value);
		break;
	case VTCFG_R_STATUS:
		vs->vs_status = value;
		if (value == 0)
			(*vc->vc_reset)(DEV_SOFTC(vs));
		break;
	case VTCFG_R_CFGVEC:
		vs->vs_msix_cfg_idx = value;
		break;
	case VTCFG_R_QVEC:
		if (vs->vs_curq >= vc->vc_nvq)
			goto bad_qindex;
		vq = &vs->vs_queues[vs->vs_curq];
		vq->vq_msix_idx = value;
		break;
	}
	goto done;

bad_qindex:
	fprintf(stderr,
	    "%s: write config reg %s: curq %d >= max %d\r\n",
	    name, cr->cr_name, vs->vs_curq, vc->vc_nvq);
done:
	if (vs->vs_mtx)
		pthread_mutex_unlock(vs->vs_mtx);
}
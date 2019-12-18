#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  void* uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_14__ {void* td_self; void* td_buffer; void* td_token; void* td_status; void* td_next; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ uhci_td_t ;
struct TYPE_17__ {int /*<<< orphan*/ * methods; int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_13__ {int /*<<< orphan*/  pframes_pc; int /*<<< orphan*/ * intr_start_pc; int /*<<< orphan*/ * isoc_start_pc; int /*<<< orphan*/  last_td_pc; int /*<<< orphan*/  last_qh_pc; int /*<<< orphan*/  bulk_start_pc; int /*<<< orphan*/  fs_ctl_start_pc; int /*<<< orphan*/  ls_ctl_start_pc; } ;
struct TYPE_15__ {TYPE_5__ sc_bus; TYPE_2__** sc_isoc_p_last; TYPE_1__ sc_hw; TYPE_2__* sc_last_td_p; TYPE_4__* sc_last_qh_p; TYPE_4__* sc_bulk_p_last; TYPE_4__* sc_fs_ctl_p_last; TYPE_4__* sc_ls_ctl_p_last; TYPE_4__** sc_intr_p_last; TYPE_4__* sc_reclaim_qh_p; int /*<<< orphan*/  sc_root_intr; } ;
typedef  TYPE_3__ uhci_softc_t ;
struct TYPE_16__ {void* qh_e_next; TYPE_2__* e_next; void* qh_h_next; struct TYPE_16__* h_next; void* qh_self; } ;
typedef  TYPE_4__ uhci_qh_t ;
struct usb_page_search {void** buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 size_t UHCI_FRAMELIST_COUNT ; 
 size_t UHCI_IFRAMELIST_COUNT ; 
 int /*<<< orphan*/  UHCI_PTR_T ; 
 int /*<<< orphan*/  UHCI_TD_IOS ; 
 size_t UHCI_VFRAMELIST_COUNT ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_5__*) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_bus_methods ; 
 int /*<<< orphan*/  uhci_do_poll (TYPE_5__*) ; 
 int /*<<< orphan*/  uhci_dumpregs (TYPE_3__*) ; 
 void* uhci_init_qh (int /*<<< orphan*/ *) ; 
 void* uhci_init_td (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_iterate_hw_softc ; 
 int /*<<< orphan*/  uhci_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  uhci_start (TYPE_3__*) ; 
 int uhcidebug ; 
 int /*<<< orphan*/  usb_bus_mem_flush_all (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_page_search*) ; 

usb_error_t
uhci_init(uhci_softc_t *sc)
{
	uint16_t bit;
	uint16_t x;
	uint16_t y;

	DPRINTF("start\n");

	usb_callout_init_mtx(&sc->sc_root_intr, &sc->sc_bus.bus_mtx, 0);

#ifdef USB_DEBUG
	if (uhcidebug > 2) {
		uhci_dumpregs(sc);
	}
#endif
	/*
	 * Setup QH's
	 */
	sc->sc_ls_ctl_p_last =
	    uhci_init_qh(&sc->sc_hw.ls_ctl_start_pc);

	sc->sc_fs_ctl_p_last =
	    uhci_init_qh(&sc->sc_hw.fs_ctl_start_pc);

	sc->sc_bulk_p_last =
	    uhci_init_qh(&sc->sc_hw.bulk_start_pc);
#if 0
	sc->sc_reclaim_qh_p =
	    sc->sc_fs_ctl_p_last;
#else
	/* setup reclaim looping point */
	sc->sc_reclaim_qh_p =
	    sc->sc_bulk_p_last;
#endif

	sc->sc_last_qh_p =
	    uhci_init_qh(&sc->sc_hw.last_qh_pc);

	sc->sc_last_td_p =
	    uhci_init_td(&sc->sc_hw.last_td_pc);

	for (x = 0; x != UHCI_VFRAMELIST_COUNT; x++) {
		sc->sc_isoc_p_last[x] =
		    uhci_init_td(sc->sc_hw.isoc_start_pc + x);
	}

	for (x = 0; x != UHCI_IFRAMELIST_COUNT; x++) {
		sc->sc_intr_p_last[x] =
		    uhci_init_qh(sc->sc_hw.intr_start_pc + x);
	}

	/*
	 * the QHs are arranged to give poll intervals that are
	 * powers of 2 times 1ms
	 */
	bit = UHCI_IFRAMELIST_COUNT / 2;
	while (bit) {
		x = bit;
		while (x & bit) {
			uhci_qh_t *qh_x;
			uhci_qh_t *qh_y;

			y = (x ^ bit) | (bit / 2);

			/*
			 * the next QH has half the poll interval
			 */
			qh_x = sc->sc_intr_p_last[x];
			qh_y = sc->sc_intr_p_last[y];

			qh_x->h_next = NULL;
			qh_x->qh_h_next = qh_y->qh_self;
			qh_x->e_next = NULL;
			qh_x->qh_e_next = htole32(UHCI_PTR_T);
			x++;
		}
		bit >>= 1;
	}

	if (1) {
		uhci_qh_t *qh_ls;
		uhci_qh_t *qh_intr;

		qh_ls = sc->sc_ls_ctl_p_last;
		qh_intr = sc->sc_intr_p_last[0];

		/* start QH for interrupt traffic */
		qh_intr->h_next = qh_ls;
		qh_intr->qh_h_next = qh_ls->qh_self;
		qh_intr->e_next = 0;
		qh_intr->qh_e_next = htole32(UHCI_PTR_T);
	}
	for (x = 0; x != UHCI_VFRAMELIST_COUNT; x++) {

		uhci_td_t *td_x;
		uhci_qh_t *qh_intr;

		td_x = sc->sc_isoc_p_last[x];
		qh_intr = sc->sc_intr_p_last[x | (UHCI_IFRAMELIST_COUNT / 2)];

		/* start TD for isochronous traffic */
		td_x->next = NULL;
		td_x->td_next = qh_intr->qh_self;
		td_x->td_status = htole32(UHCI_TD_IOS);
		td_x->td_token = htole32(0);
		td_x->td_buffer = htole32(0);
	}

	if (1) {
		uhci_qh_t *qh_ls;
		uhci_qh_t *qh_fs;

		qh_ls = sc->sc_ls_ctl_p_last;
		qh_fs = sc->sc_fs_ctl_p_last;

		/* start QH where low speed control traffic will be queued */
		qh_ls->h_next = qh_fs;
		qh_ls->qh_h_next = qh_fs->qh_self;
		qh_ls->e_next = 0;
		qh_ls->qh_e_next = htole32(UHCI_PTR_T);
	}
	if (1) {
		uhci_qh_t *qh_ctl;
		uhci_qh_t *qh_blk;
		uhci_qh_t *qh_lst;
		uhci_td_t *td_lst;

		qh_ctl = sc->sc_fs_ctl_p_last;
		qh_blk = sc->sc_bulk_p_last;

		/* start QH where full speed control traffic will be queued */
		qh_ctl->h_next = qh_blk;
		qh_ctl->qh_h_next = qh_blk->qh_self;
		qh_ctl->e_next = 0;
		qh_ctl->qh_e_next = htole32(UHCI_PTR_T);

		qh_lst = sc->sc_last_qh_p;

		/* start QH where bulk traffic will be queued */
		qh_blk->h_next = qh_lst;
		qh_blk->qh_h_next = qh_lst->qh_self;
		qh_blk->e_next = 0;
		qh_blk->qh_e_next = htole32(UHCI_PTR_T);

		td_lst = sc->sc_last_td_p;

		/* end QH which is used for looping the QHs */
		qh_lst->h_next = 0;
		qh_lst->qh_h_next = htole32(UHCI_PTR_T);	/* end of QH chain */
		qh_lst->e_next = td_lst;
		qh_lst->qh_e_next = td_lst->td_self;

		/*
		 * end TD which hangs from the last QH, to avoid a bug in the PIIX
		 * that makes it run berserk otherwise
		 */
		td_lst->next = 0;
		td_lst->td_next = htole32(UHCI_PTR_T);
		td_lst->td_status = htole32(0);	/* inactive */
		td_lst->td_token = htole32(0);
		td_lst->td_buffer = htole32(0);
	}
	if (1) {
		struct usb_page_search buf_res;
		uint32_t *pframes;

		usbd_get_page(&sc->sc_hw.pframes_pc, 0, &buf_res);

		pframes = buf_res.buffer;


		/*
		 * Setup UHCI framelist
		 *
		 * Execution order:
		 *
		 * pframes -> full speed isochronous -> interrupt QH's -> low
		 * speed control -> full speed control -> bulk transfers
		 *
		 */

		for (x = 0; x != UHCI_FRAMELIST_COUNT; x++) {
			pframes[x] =
			    sc->sc_isoc_p_last[x % UHCI_VFRAMELIST_COUNT]->td_self;
		}
	}
	/* flush all cache into memory */

	usb_bus_mem_flush_all(&sc->sc_bus, &uhci_iterate_hw_softc);

	/* set up the bus struct */
	sc->sc_bus.methods = &uhci_bus_methods;

	USB_BUS_LOCK(&sc->sc_bus);
	/* reset the controller */
	uhci_reset(sc);

	/* start the controller */
	uhci_start(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch lost interrupts */
	uhci_do_poll(&sc->sc_bus);

	return (0);
}
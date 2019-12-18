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
struct nmreq_vale_newif {int /*<<< orphan*/  nr_mem_id; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; } ;
struct nmreq_vale_list {int /*<<< orphan*/  nr_port_idx; int /*<<< orphan*/  nr_bridge_idx; } ;
struct nmreq_register {int dummy; } ;
struct nmreq_vale_attach {struct nmreq_register reg; } ;
struct nmreq_port_info_get {int /*<<< orphan*/  nr_mem_id; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_memsize; } ;
struct nmreq_port_hdr {int /*<<< orphan*/  nr_hdr_len; } ;
struct nmreq_header {int nr_reqtype; int /*<<< orphan*/  nr_body; int /*<<< orphan*/  nr_name; } ;
struct nmreq {int /*<<< orphan*/  nr_arg2; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_arg1; int /*<<< orphan*/  nr_name; int /*<<< orphan*/  nr_memsize; } ;

/* Variables and functions */
#define  NETMAP_REQ_PORT_HDR_GET 138 
#define  NETMAP_REQ_PORT_HDR_SET 137 
#define  NETMAP_REQ_PORT_INFO_GET 136 
#define  NETMAP_REQ_REGISTER 135 
#define  NETMAP_REQ_VALE_ATTACH 134 
#define  NETMAP_REQ_VALE_DELIF 133 
#define  NETMAP_REQ_VALE_DETACH 132 
#define  NETMAP_REQ_VALE_LIST 131 
#define  NETMAP_REQ_VALE_NEWIF 130 
#define  NETMAP_REQ_VALE_POLLING_DISABLE 129 
#define  NETMAP_REQ_VALE_POLLING_ENABLE 128 
 int /*<<< orphan*/  nmreq_register_to_legacy (struct nmreq_register*,struct nmreq*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nmreq_to_legacy(struct nmreq_header *hdr, struct nmreq *nmr)
{
	int ret = 0;

	/* We only write-back the fields that the user expects to be
	 * written back. */
	switch (hdr->nr_reqtype) {
	case NETMAP_REQ_REGISTER: {
		struct nmreq_register *req =
			(struct nmreq_register *)(uintptr_t)hdr->nr_body;
		nmreq_register_to_legacy(req, nmr);
		break;
	}
	case NETMAP_REQ_PORT_INFO_GET: {
		struct nmreq_port_info_get *req =
			(struct nmreq_port_info_get *)(uintptr_t)hdr->nr_body;
		nmr->nr_memsize = req->nr_memsize;
		nmr->nr_tx_slots = req->nr_tx_slots;
		nmr->nr_rx_slots = req->nr_rx_slots;
		nmr->nr_tx_rings = req->nr_tx_rings;
		nmr->nr_rx_rings = req->nr_rx_rings;
		nmr->nr_arg2 = req->nr_mem_id;
		break;
	}
	case NETMAP_REQ_VALE_ATTACH: {
		struct nmreq_vale_attach *req =
			(struct nmreq_vale_attach *)(uintptr_t)hdr->nr_body;
		nmreq_register_to_legacy(&req->reg, nmr);
		break;
	}
	case NETMAP_REQ_VALE_DETACH: {
		break;
	}
	case NETMAP_REQ_VALE_LIST: {
		struct nmreq_vale_list *req =
			(struct nmreq_vale_list *)(uintptr_t)hdr->nr_body;
		strlcpy(nmr->nr_name, hdr->nr_name, sizeof(nmr->nr_name));
		nmr->nr_arg1 = req->nr_bridge_idx;
		nmr->nr_arg2 = req->nr_port_idx;
		break;
	}
	case NETMAP_REQ_PORT_HDR_SET:
	case NETMAP_REQ_PORT_HDR_GET: {
		struct nmreq_port_hdr *req =
			(struct nmreq_port_hdr *)(uintptr_t)hdr->nr_body;
		nmr->nr_arg1 = req->nr_hdr_len;
		break;
	}
	case NETMAP_REQ_VALE_NEWIF: {
		struct nmreq_vale_newif *req =
			(struct nmreq_vale_newif *)(uintptr_t)hdr->nr_body;
		nmr->nr_tx_slots = req->nr_tx_slots;
		nmr->nr_rx_slots = req->nr_rx_slots;
		nmr->nr_tx_rings = req->nr_tx_rings;
		nmr->nr_rx_rings = req->nr_rx_rings;
		nmr->nr_arg2 = req->nr_mem_id;
		break;
	}
	case NETMAP_REQ_VALE_DELIF:
	case NETMAP_REQ_VALE_POLLING_ENABLE:
	case NETMAP_REQ_VALE_POLLING_DISABLE: {
		break;
	}
	}

	return ret;
}
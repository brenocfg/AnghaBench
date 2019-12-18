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
struct ntb_transport_qp {int tx_max_frame; int tx_index; int /*<<< orphan*/  tx_pkts; void* tx_mw; } ;
struct ntb_queue_entry {int /*<<< orphan*/  len; struct ntb_payload_header* x_hdr; } ;
struct ntb_payload_header {int /*<<< orphan*/  ver; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_memcpy_tx (struct ntb_queue_entry*,void*) ; 

__attribute__((used)) static void
ntb_async_tx(struct ntb_transport_qp *qp, struct ntb_queue_entry *entry)
{
	struct ntb_payload_header *hdr;
	void *offset;

	offset = qp->tx_mw + qp->tx_max_frame * qp->tx_index;
	hdr = (struct ntb_payload_header *)((char *)offset + qp->tx_max_frame -
	    sizeof(struct ntb_payload_header));
	entry->x_hdr = hdr;

	iowrite32(entry->len, &hdr->len);
	iowrite32(qp->tx_pkts, &hdr->ver);

	ntb_memcpy_tx(entry, offset);
}
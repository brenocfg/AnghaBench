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
struct ntb_transport_qp {int dummy; } ;
struct ntb_queue_entry {unsigned int len; int /*<<< orphan*/ * buf; struct ifnet* cb_data; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int ENOMEM ; 
 int /*<<< orphan*/  KTR_NTB ; 
 scalar_t__ m_devget (void*,unsigned int,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_rx_copy_callback (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ntb_memcpy_rx(struct ntb_transport_qp *qp, struct ntb_queue_entry *entry,
    void *offset)
{
	struct ifnet *ifp = entry->cb_data;
	unsigned int len = entry->len;

	CTR2(KTR_NTB, "RX: copying %d bytes from offset %p", len, offset);

	entry->buf = (void *)m_devget(offset, len, 0, ifp, NULL);
	if (entry->buf == NULL)
		entry->len = -ENOMEM;

	/* Ensure that the data is globally visible before clearing the flag */
	wmb();

	CTR2(KTR_NTB, "RX: copied entry %p to mbuf %p.", entry, entry->buf);
	ntb_rx_copy_callback(qp, entry);
}
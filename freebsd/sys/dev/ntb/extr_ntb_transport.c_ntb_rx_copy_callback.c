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
struct ntb_queue_entry {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTBT_DESC_DONE_FLAG ; 
 int /*<<< orphan*/  ntb_complete_rxc (struct ntb_transport_qp*) ; 

__attribute__((used)) static inline void
ntb_rx_copy_callback(struct ntb_transport_qp *qp, void *data)
{
	struct ntb_queue_entry *entry;

	entry = data;
	entry->flags |= NTBT_DESC_DONE_FLAG;
	ntb_complete_rxc(qp);
}
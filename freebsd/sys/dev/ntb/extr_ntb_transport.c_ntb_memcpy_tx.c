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
struct ntb_queue_entry {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  KTR_NTB ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ntb_tx_copy_callback (struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ntb_memcpy_tx(struct ntb_queue_entry *entry, void *offset)
{

	CTR2(KTR_NTB, "TX: copying %d bytes to offset %p", entry->len, offset);
	if (entry->buf != NULL) {
		m_copydata((struct mbuf *)entry->buf, 0, entry->len, offset);

		/*
		 * Ensure that the data is fully copied before setting the
		 * flags
		 */
		wmb();
	}

	ntb_tx_copy_callback(entry);
}
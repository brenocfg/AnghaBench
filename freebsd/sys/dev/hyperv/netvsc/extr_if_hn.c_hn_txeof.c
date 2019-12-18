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
struct hn_tx_ring {int /*<<< orphan*/  (* hn_txeof ) (struct hn_tx_ring*) ;scalar_t__ hn_has_txeof; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hn_tx_ring*) ; 

__attribute__((used)) static __inline void
hn_txeof(struct hn_tx_ring *txr)
{
	txr->hn_has_txeof = 0;
	txr->hn_txeof(txr);
}
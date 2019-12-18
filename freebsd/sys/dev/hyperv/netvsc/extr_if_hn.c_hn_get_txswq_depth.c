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
struct hn_tx_ring {scalar_t__ hn_txdesc_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ hn_tx_swq_depth ; 

__attribute__((used)) static int
hn_get_txswq_depth(const struct hn_tx_ring *txr)
{

	KASSERT(txr->hn_txdesc_cnt > 0, ("tx ring is not setup yet"));
	if (hn_tx_swq_depth < txr->hn_txdesc_cnt)
		return txr->hn_txdesc_cnt;
	return hn_tx_swq_depth;
}
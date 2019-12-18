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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u16 ;
struct qlnx_tx_queue {int /*<<< orphan*/  tx_pbl; int /*<<< orphan*/ * hw_cons_ptr; } ;
struct qlnx_fastpath {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 scalar_t__ ecore_chain_get_cons_idx (int /*<<< orphan*/ *) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
qlnx_num_tx_compl(qlnx_host_t *ha, struct qlnx_fastpath *fp,
	struct qlnx_tx_queue *txq)
{
	u16 hw_bd_cons;
	u16 ecore_cons_idx;
	uint16_t diff;

	hw_bd_cons = le16toh(*txq->hw_cons_ptr);

	ecore_cons_idx = ecore_chain_get_cons_idx(&txq->tx_pbl);
	if (hw_bd_cons < ecore_cons_idx) {
		diff = (1 << 16) - (ecore_cons_idx - hw_bd_cons);
	} else {
		diff = hw_bd_cons - ecore_cons_idx;
	}
	return diff;
}
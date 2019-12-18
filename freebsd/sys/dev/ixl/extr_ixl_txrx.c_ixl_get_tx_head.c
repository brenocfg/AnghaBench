#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tx_ring {int /*<<< orphan*/ * tx_base; } ;
struct ixl_tx_queue {struct tx_ring txr; TYPE_1__* vsi; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {size_t* isc_ntxd; } ;
struct TYPE_3__ {TYPE_2__* shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE32_TO_CPU (int /*<<< orphan*/  volatile) ; 

__attribute__((used)) static inline u32
ixl_get_tx_head(struct ixl_tx_queue *que)
{
	if_softc_ctx_t          scctx = que->vsi->shared;
	struct tx_ring  *txr = &que->txr;
	void *head = &txr->tx_base[scctx->isc_ntxd[0]];

	return LE32_TO_CPU(*(volatile __le32 *)head);
}
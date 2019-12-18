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
struct vtnet_rxq {int /*<<< orphan*/  vtnrx_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_disable_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtnet_rxq_disable_intr(struct vtnet_rxq *rxq)
{

	virtqueue_disable_intr(rxq->vtnrx_vq);
}
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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bwn_pio_rxqueue {scalar_t__ prq_base; int /*<<< orphan*/  prq_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_READ_4 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t
bwn_pio_rx_read_4(struct bwn_pio_rxqueue *prq, uint16_t offset)
{

	return (BWN_READ_4(prq->prq_mac, prq->prq_base + offset));
}
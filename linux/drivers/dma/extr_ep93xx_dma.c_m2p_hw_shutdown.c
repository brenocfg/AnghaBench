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
struct ep93xx_dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ M2P_STATE_IDLE ; 
 int /*<<< orphan*/  chan2dev (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ m2p_channel_state (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2p_set_control (struct ep93xx_dma_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m2p_hw_shutdown(struct ep93xx_dma_chan *edmac)
{
	m2p_set_control(edmac, 0);

	while (m2p_channel_state(edmac) != M2P_STATE_IDLE)
		dev_warn(chan2dev(edmac), "M2P: Not yet IDLE\n");
}
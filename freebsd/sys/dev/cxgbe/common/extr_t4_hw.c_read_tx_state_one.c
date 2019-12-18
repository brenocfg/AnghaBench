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
struct port_tx_state {void* tx_frames; void* rx_pause; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MPS_PORT_STAT_RX_PORT_PAUSE_L ; 
 int /*<<< orphan*/  A_MPS_PORT_STAT_TX_PORT_FRAMES_L ; 
 int /*<<< orphan*/  PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T5_PORT_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 void* t4_read_reg64 (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_tx_state_one(struct adapter *sc, int i, struct port_tx_state *tx_state)
{
	uint32_t rx_pause_reg, tx_frames_reg;

	if (is_t4(sc)) {
		tx_frames_reg = PORT_REG(i, A_MPS_PORT_STAT_TX_PORT_FRAMES_L);
		rx_pause_reg = PORT_REG(i, A_MPS_PORT_STAT_RX_PORT_PAUSE_L);
	} else {
		tx_frames_reg = T5_PORT_REG(i, A_MPS_PORT_STAT_TX_PORT_FRAMES_L);
		rx_pause_reg = T5_PORT_REG(i, A_MPS_PORT_STAT_RX_PORT_PAUSE_L);
	}

	tx_state->rx_pause = t4_read_reg64(sc, rx_pause_reg);
	tx_state->tx_frames = t4_read_reg64(sc, tx_frames_reg);
}
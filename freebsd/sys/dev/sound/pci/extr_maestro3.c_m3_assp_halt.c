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
typedef  int u_int8_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DSP_PORT_CONTROL_REG_B ; 
 int /*<<< orphan*/  M3_LOCK_ASSERT (struct sc_info*) ; 
 int REGB_ENABLE_RESET ; 
 int REGB_STOP_CLOCK ; 
 int m3_rd_1 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_1 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int8_t
m3_assp_halt(struct sc_info *sc)
{
	u_int8_t data, reset_state;

	M3_LOCK_ASSERT(sc);

	data = m3_rd_1(sc, DSP_PORT_CONTROL_REG_B);
	reset_state = data & ~REGB_STOP_CLOCK; /* remember for continue */
        DELAY(10 * 1000);
	m3_wr_1(sc, DSP_PORT_CONTROL_REG_B, reset_state & ~REGB_ENABLE_RESET);
        DELAY(10 * 1000); /* necessary? */

	return reset_state;
}
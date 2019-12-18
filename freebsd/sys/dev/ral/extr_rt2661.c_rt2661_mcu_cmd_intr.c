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
struct rt2661_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_M2H_CMD_DONE_CSR ; 

__attribute__((used)) static void
rt2661_mcu_cmd_intr(struct rt2661_softc *sc)
{
	RAL_READ(sc, RT2661_M2H_CMD_DONE_CSR);
	RAL_WRITE(sc, RT2661_M2H_CMD_DONE_CSR, 0xffffffff);
}
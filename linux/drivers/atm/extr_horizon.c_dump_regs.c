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
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_0_REG ; 
 int /*<<< orphan*/  DBG_REGS ; 
 int /*<<< orphan*/  INT_ENABLE_REG_OFF ; 
 int /*<<< orphan*/  INT_SOURCE_REG_OFF ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_CONFIG_OFF ; 
 int /*<<< orphan*/  TX_CONFIG_OFF ; 
 int /*<<< orphan*/  TX_STATUS_OFF ; 
 int /*<<< orphan*/  rd_regl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_regw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_regs (hrz_dev * dev) {
#ifdef DEBUG_HORIZON
  PRINTD (DBG_REGS, "CONTROL 0: %#x", rd_regl (dev, CONTROL_0_REG));
  PRINTD (DBG_REGS, "RX CONFIG: %#x", rd_regw (dev, RX_CONFIG_OFF));
  PRINTD (DBG_REGS, "TX CONFIG: %#x", rd_regw (dev, TX_CONFIG_OFF));
  PRINTD (DBG_REGS, "TX STATUS: %#x", rd_regw (dev, TX_STATUS_OFF));
  PRINTD (DBG_REGS, "IRQ ENBLE: %#x", rd_regl (dev, INT_ENABLE_REG_OFF));
  PRINTD (DBG_REGS, "IRQ SORCE: %#x", rd_regl (dev, INT_SOURCE_REG_OFF));
#else
  (void) dev;
#endif
  return;
}
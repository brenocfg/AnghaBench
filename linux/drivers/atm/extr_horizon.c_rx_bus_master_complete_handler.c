#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ hrz_dev ;

/* Variables and functions */
 int DBG_ERR ; 
 int DBG_RX ; 
 int /*<<< orphan*/  MASTER_RX_COUNT_REG_OFF ; 
 int /*<<< orphan*/  PRINTD (int,char*) ; 
 int /*<<< orphan*/  rx_busy ; 
 int /*<<< orphan*/  rx_schedule (TYPE_1__*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_regl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_bus_master_complete_handler (hrz_dev * dev) {
  if (test_bit (rx_busy, &dev->flags)) {
    rx_schedule (dev, 1);
  } else {
    PRINTD (DBG_RX|DBG_ERR, "unexpected RX bus master completion");
    // clear interrupt condition on adapter
    wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
  }
  return;
}
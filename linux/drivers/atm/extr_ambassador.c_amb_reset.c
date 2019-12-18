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
typedef  int u32 ;
typedef  int /*<<< orphan*/  amb_dev ;
struct TYPE_3__ {int /*<<< orphan*/  result; int /*<<< orphan*/  ready; } ;
struct TYPE_4__ {TYPE_1__ loader; } ;

/* Variables and functions */
 int AMB_DOORBELL_BITS ; 
 int AMB_RESET_BITS ; 
 int DBG_ERR ; 
 int DBG_FLOW ; 
 int DBG_LOAD ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int GPINT_TST_FAILURE ; 
 int /*<<< orphan*/  PRINTD (int,char*) ; 
 int SELF_TEST_FAILURE ; 
 int SRAM_FAILURE ; 
 int SUNI_DATA_BITS_FAILURE ; 
 int SUNI_DATA_PATTERN_FAILURE ; 
 int SUNI_FIFO_FAILURE ; 
 int SUNI_UTOPIA_FAILURE ; 
 int /*<<< orphan*/  amb_mem ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  interrupt_control ; 
 TYPE_2__ mb ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned long msleep_interruptible (unsigned long) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rd_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rd_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control ; 
 int /*<<< orphan*/  sf (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amb_reset (amb_dev * dev, int diags) {
  u32 word;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "amb_reset");
  
  word = rd_plain (dev, offsetof(amb_mem, reset_control));
  // put card into reset state
  wr_plain (dev, offsetof(amb_mem, reset_control), word | AMB_RESET_BITS);
  // wait a short while
  udelay (10);
#if 1
  // put card into known good state
  wr_plain (dev, offsetof(amb_mem, interrupt_control), AMB_DOORBELL_BITS);
  // clear all interrupts just in case
  wr_plain (dev, offsetof(amb_mem, interrupt), -1);
#endif
  // clear self-test done flag
  wr_plain (dev, offsetof(amb_mem, mb.loader.ready), 0);
  // take card out of reset state
  wr_plain (dev, offsetof(amb_mem, reset_control), word &~ AMB_RESET_BITS);
  
  if (diags) { 
    unsigned long timeout;
    // 4.2 second wait
    msleep(4200);
    // half second time-out
    timeout = 500;
    while (!rd_plain (dev, offsetof(amb_mem, mb.loader.ready)))
      if (timeout) {
	timeout = msleep_interruptible(timeout);
      } else {
	PRINTD (DBG_LOAD|DBG_ERR, "reset timed out");
	return -ETIMEDOUT;
      }
    
    // get results of self-test
    // XXX double check byte-order
    word = rd_mem (dev, offsetof(amb_mem, mb.loader.result));
    if (word & SELF_TEST_FAILURE) {
      if (word & GPINT_TST_FAILURE)
	sf ("interrupt");
      if (word & SUNI_DATA_PATTERN_FAILURE)
	sf ("SUNI data pattern");
      if (word & SUNI_DATA_BITS_FAILURE)
	sf ("SUNI data bits");
      if (word & SUNI_UTOPIA_FAILURE)
	sf ("SUNI UTOPIA interface");
      if (word & SUNI_FIFO_FAILURE)
	sf ("SUNI cell buffer FIFO");
      if (word & SRAM_FAILURE)
	sf ("bad SRAM");
      // better return value?
      return -EIO;
    }
    
  }
  return 0;
}
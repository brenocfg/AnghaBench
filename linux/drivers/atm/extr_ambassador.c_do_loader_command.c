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
typedef  size_t loader_command ;
struct TYPE_5__ {void* result; void* valid; void* command; } ;
typedef  TYPE_1__ loader_block ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 size_t COMMAND_IN_PROGRESS ; 
 int DBG_ERR ; 
 int DBG_FLOW ; 
 int DBG_LOAD ; 
 size_t DMA_VALID ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 size_t adapter_start ; 
 int /*<<< orphan*/  amb_mem ; 
 size_t be32_to_cpu (void*) ; 
 int* command_timeouts ; 
 void* cpu_to_be32 (size_t) ; 
 int decode_loader_result (size_t,size_t) ; 
 int /*<<< orphan*/  doorbell ; 
 int /*<<< orphan*/  dump_loader_block (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  dump_registers (int /*<<< orphan*/  const*) ; 
 unsigned long msleep_interruptible (unsigned long) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int onegigmask ; 
 scalar_t__ rd_plain (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int virt_to_bus (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  wr_mem (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_loader_command(volatile loader_block *lb, const amb_dev *dev,
			     loader_command cmd)
{
  
  unsigned long timeout;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "do_loader_command");
  
  /* do a command
     
     Set the return value to zero, set the command type and set the
     valid entry to the right magic value. The payload is already
     correctly byte-ordered so we leave it alone. Hit the doorbell
     with the bus address of this structure.
     
  */
  
  lb->result = 0;
  lb->command = cpu_to_be32 (cmd);
  lb->valid = cpu_to_be32 (DMA_VALID);
  // dump_registers (dev);
  // dump_loader_block (lb);
  wr_mem (dev, offsetof(amb_mem, doorbell), virt_to_bus (lb) & ~onegigmask);
  
  timeout = command_timeouts[cmd] * 10;
  
  while (!lb->result || lb->result == cpu_to_be32 (COMMAND_IN_PROGRESS))
    if (timeout) {
      timeout = msleep_interruptible(timeout);
    } else {
      PRINTD (DBG_LOAD|DBG_ERR, "command %d timed out", cmd);
      dump_registers (dev);
      dump_loader_block (lb);
      return -ETIMEDOUT;
    }
  
  if (cmd == adapter_start) {
    // wait for start command to acknowledge...
    timeout = 100;
    while (rd_plain (dev, offsetof(amb_mem, doorbell)))
      if (timeout) {
	timeout = msleep_interruptible(timeout);
      } else {
	PRINTD (DBG_LOAD|DBG_ERR, "start command did not clear doorbell, res=%08x",
		be32_to_cpu (lb->result));
	dump_registers (dev);
	return -ETIMEDOUT;
      }
    return 0;
  } else {
    return decode_loader_result (cmd, be32_to_cpu (lb->result));
  }
  
}
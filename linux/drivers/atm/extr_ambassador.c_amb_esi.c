#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  upper2; int /*<<< orphan*/  lower4; } ;
struct TYPE_6__ {TYPE_1__ bia; } ;
struct TYPE_7__ {TYPE_2__ args; int /*<<< orphan*/  request; } ;
typedef  TYPE_3__ command ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INIT ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 unsigned int ESI_LEN ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  PRINTDB (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRINTDE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRINTDM (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRB_GET_BIA ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitrev8 (int) ; 
 scalar_t__ command_do (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amb_esi(amb_dev *dev, u8 *esi)
{
  u32 lower4;
  u16 upper2;
  command cmd;
  
  cmd.request = cpu_to_be32 (SRB_GET_BIA);
  while (command_do (dev, &cmd)) {
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule();
  }
  lower4 = be32_to_cpu (cmd.args.bia.lower4);
  upper2 = be32_to_cpu (cmd.args.bia.upper2);
  PRINTD (DBG_LOAD, "BIA: lower4: %08x, upper2 %04x", lower4, upper2);
  
  if (esi) {
    unsigned int i;
    
    PRINTDB (DBG_INIT, "ESI:");
    for (i = 0; i < ESI_LEN; ++i) {
      if (i < 4)
	  esi[i] = bitrev8(lower4>>(8*i));
      else
	  esi[i] = bitrev8(upper2>>(8*(i-4)));
      PRINTDM (DBG_INIT, " %02x", esi[i]);
    }
    
    PRINTDE (DBG_INIT, "");
  }
  
  return;
}
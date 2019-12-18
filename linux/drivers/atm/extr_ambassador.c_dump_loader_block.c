#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int /*<<< orphan*/  valid; TYPE_1__ payload; int /*<<< orphan*/  command; int /*<<< orphan*/  result; } ;
typedef  TYPE_2__ loader_block ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOAD ; 
 unsigned int MAX_COMMAND_DATA ; 
 int /*<<< orphan*/  PRINTDB (int /*<<< orphan*/ ,char*,TYPE_2__ volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTDE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTDM (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_loader_block (volatile loader_block * lb) {
#ifdef DEBUG_AMBASSADOR
  unsigned int i;
  PRINTDB (DBG_LOAD, "lb @ %p; res: %d, cmd: %d, pay:",
	   lb, be32_to_cpu (lb->result), be32_to_cpu (lb->command));
  for (i = 0; i < MAX_COMMAND_DATA; ++i)
    PRINTDM (DBG_LOAD, " %08x", be32_to_cpu (lb->payload.data[i]));
  PRINTDE (DBG_LOAD, ", vld: %08x", be32_to_cpu (lb->valid));
#else
  (void) lb;
#endif
  return;
}
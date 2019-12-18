#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* flags; } ;
struct TYPE_12__ {TYPE_1__ flush; } ;
struct TYPE_13__ {TYPE_2__ args; void* request; } ;
typedef  TYPE_3__ command ;
struct TYPE_14__ {scalar_t__ pending; scalar_t__ buffers_wanted; } ;
typedef  TYPE_4__ amb_rxq ;
struct TYPE_15__ {int /*<<< orphan*/  flags; TYPE_4__* rxq; } ;
typedef  TYPE_5__ amb_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_POOL ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_5__*,unsigned char) ; 
 unsigned char SRB_FLUSH_BUFFER_Q ; 
 unsigned char SRB_POOL_SHIFT ; 
 scalar_t__ command_do (TYPE_5__*,TYPE_3__*) ; 
 void* cpu_to_be32 (unsigned char) ; 
 int /*<<< orphan*/  dead ; 
 scalar_t__ rx_take (TYPE_5__*,unsigned char) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drain_rx_pool (amb_dev * dev, unsigned char pool) {
  amb_rxq * rxq = &dev->rxq[pool];
  
  PRINTD (DBG_FLOW|DBG_POOL, "drain_rx_pool %p %hu", dev, pool);
  
  if (test_bit (dead, &dev->flags))
    return;
  
  /* we are not quite like the fill pool routines as we cannot just
     remove one buffer, we have to remove all of them, but we might as
     well pretend... */
  if (rxq->pending > rxq->buffers_wanted) {
    command cmd;
    cmd.request = cpu_to_be32 (SRB_FLUSH_BUFFER_Q);
    cmd.args.flush.flags = cpu_to_be32 (pool << SRB_POOL_SHIFT);
    while (command_do (dev, &cmd))
      schedule();
    /* the pool may also be emptied via the interrupt handler */
    while (rxq->pending > rxq->buffers_wanted)
      if (rx_take (dev, pool))
	schedule();
  }
  
  return;
}
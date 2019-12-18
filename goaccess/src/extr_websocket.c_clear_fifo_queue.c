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
struct TYPE_5__ {scalar_t__ qlen; struct TYPE_5__* queued; } ;
typedef  TYPE_1__ WSQueue ;
struct TYPE_6__ {TYPE_1__* fifoqueue; } ;
typedef  TYPE_2__ WSPipeOut ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
clear_fifo_queue (WSPipeOut * pipeout)
{
  WSQueue **queue = &pipeout->fifoqueue;
  if (!(*queue))
    return;

  if ((*queue)->queued)
    free ((*queue)->queued);
  (*queue)->queued = NULL;
  (*queue)->qlen = 0;

  free ((*queue));
  (*queue) = NULL;
}
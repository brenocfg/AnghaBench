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
struct TYPE_6__ {int status; TYPE_1__* sockqueue; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int WS_SENDING ; 
 int WS_THROTTLING ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
ws_clear_queue (WSClient * client)
{
  WSQueue **queue = &client->sockqueue;
  if (!(*queue))
    return;

  if ((*queue)->queued)
    free ((*queue)->queued);
  (*queue)->queued = NULL;
  (*queue)->qlen = 0;

  free ((*queue));
  (*queue) = NULL;

  /* done sending the whole queue, stop throttling */
  client->status &= ~WS_THROTTLING;
  /* done sending, close connection if set to close */
  if ((client->status & WS_CLOSE) && (client->status & WS_SENDING))
    client->status = WS_CLOSE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int qlen; void* queued; } ;
typedef  TYPE_1__ WSQueue ;
struct TYPE_5__ {int /*<<< orphan*/  status; TYPE_1__* sockqueue; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int /*<<< orphan*/  WS_SENDING ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static void
ws_queue_sockbuf (WSClient * client, const char *buffer, int len, int bytes)
{
  WSQueue *queue = xcalloc (1, sizeof (WSQueue));

  if (bytes < 1)
    bytes = 0;

  queue->queued = xcalloc (len - bytes, sizeof (char));
  memcpy (queue->queued, buffer + bytes, len - bytes);
  queue->qlen = len - bytes;
  client->sockqueue = queue;

  client->status |= WS_SENDING;
}
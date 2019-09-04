#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int qlen; int /*<<< orphan*/  queued; } ;
typedef  TYPE_1__ WSQueue ;
struct TYPE_8__ {TYPE_1__* sockqueue; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EPIPE ; 
 scalar_t__ EWOULDBLOCK ; 
 int WS_CLOSE ; 
 int WS_ERR ; 
 scalar_t__ chop_nchars (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ errno ; 
 int send_buffer (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ws_clear_queue (TYPE_2__*) ; 
 int ws_set_status (TYPE_2__*,int,int) ; 

__attribute__((used)) static int
ws_respond_cache (WSClient * client)
{
  WSQueue *queue = client->sockqueue;
  int bytes = 0;

  bytes = send_buffer (client, queue->queued, queue->qlen);
  if (bytes == -1 && errno == EPIPE)
    return ws_set_status (client, WS_ERR | WS_CLOSE, bytes);

  if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
    return bytes;

  if (chop_nchars (queue->queued, bytes, queue->qlen) == 0)
    ws_clear_queue (client);
  else
    queue->qlen -= bytes;

  return bytes;
}
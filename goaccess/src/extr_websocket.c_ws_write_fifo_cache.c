#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int qlen; int /*<<< orphan*/  queued; } ;
typedef  TYPE_1__ WSQueue ;
struct TYPE_7__ {int /*<<< orphan*/  fd; TYPE_1__* fifoqueue; } ;
typedef  TYPE_2__ WSPipeOut ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 scalar_t__ chop_nchars (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clear_fifo_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ws_openfifo_out (TYPE_2__*) ; 

__attribute__((used)) static int
ws_write_fifo_cache (WSPipeOut * pipeout)
{
  WSQueue *queue = pipeout->fifoqueue;
  int bytes = 0;

  bytes = write (pipeout->fd, queue->queued, queue->qlen);

  /* At this point, the reader probably closed the pipe, so a cheap *hack* for
   * this is to close the pipe on our end and attempt to reopen it. If unable to
   * do so, then let it be -1 and try on the next attempt to write. */
  if (bytes == -1 && errno == EPIPE) {
    close (pipeout->fd);
    ws_openfifo_out (pipeout);
    return bytes;
  }

  if (chop_nchars (queue->queued, bytes, queue->qlen) == 0)
    clear_fifo_queue (pipeout);
  else
    queue->qlen -= bytes;

  return bytes;
}
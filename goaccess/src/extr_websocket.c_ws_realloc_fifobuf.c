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
struct TYPE_6__ {int qlen; char* queued; } ;
typedef  TYPE_1__ WSQueue ;
struct TYPE_7__ {int /*<<< orphan*/  fd; TYPE_1__* fifoqueue; } ;
typedef  TYPE_2__ WSPipeOut ;

/* Variables and functions */
 int /*<<< orphan*/  clear_fifo_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  ws_openfifo_out (TYPE_2__*) ; 

__attribute__((used)) static int
ws_realloc_fifobuf (WSPipeOut * pipeout, const char *buf, int len)
{
  WSQueue *queue = pipeout->fifoqueue;
  char *tmp = NULL;
  int newlen = 0;

  newlen = queue->qlen + len;
  tmp = realloc (queue->queued, newlen);
  if (tmp == NULL && newlen > 0) {
    close (pipeout->fd);
    clear_fifo_queue (pipeout);
    ws_openfifo_out (pipeout);
    return 1;
  }

  queue->queued = tmp;
  memcpy (queue->queued + queue->qlen, buf, len);
  queue->qlen += len;

  return 0;
}
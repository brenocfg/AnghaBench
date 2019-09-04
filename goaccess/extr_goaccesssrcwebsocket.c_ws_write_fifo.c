#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; int /*<<< orphan*/  status; int /*<<< orphan*/ * fifoqueue; } ;
typedef  TYPE_1__ WSPipeOut ;

/* Variables and functions */
 int /*<<< orphan*/  WS_SENDING ; 
 int ws_openfifo_out (TYPE_1__*) ; 
 int ws_realloc_fifobuf (TYPE_1__*,char*,int) ; 
 int ws_write_fifo_cache (TYPE_1__*) ; 
 int ws_write_fifo_data (TYPE_1__*,char*,int) ; 

int
ws_write_fifo (WSPipeOut * pipeout, char *buffer, int len)
{
  int bytes = 0;

  if (pipeout->fd == -1 && ws_openfifo_out (pipeout) == -1)
    return bytes;

  /* attempt to send the whole buffer buffer */
  if (pipeout->fifoqueue == NULL)
    bytes = ws_write_fifo_data (pipeout, buffer, len);
  /* buffer not empty, just append new data */
  else if (pipeout->fifoqueue != NULL && buffer != NULL) {
    if (ws_realloc_fifobuf (pipeout, buffer, len) == 1)
      return bytes;
  }
  /* send from cache buffer */
  else {
    bytes = ws_write_fifo_cache (pipeout);
  }

  if (pipeout->fifoqueue == NULL)
    pipeout->status &= ~WS_SENDING;

  return bytes;
}
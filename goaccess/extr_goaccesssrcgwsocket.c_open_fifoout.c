#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* fifo_out; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDWR ; 
 char* WS_PIPEOUT ; 
 TYPE_1__ conf ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  ws_setfifo (char const*) ; 

int
open_fifoout (void)
{
  const char *fifo = conf.fifo_out ? conf.fifo_out : WS_PIPEOUT;
  int fdfifo;

  /* open fifo for reading before writing */
  ws_setfifo (fifo);
  if ((fdfifo = open (fifo, O_RDWR | O_NONBLOCK)) == -1)
    return -1;

  return fdfifo;
}
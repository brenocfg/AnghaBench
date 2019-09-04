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
struct TYPE_4__ {int fd; } ;
typedef  TYPE_1__ WSPipeOut ;
struct TYPE_5__ {int /*<<< orphan*/  pipeout; } ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 scalar_t__ errno ; 
 int max_file_fd ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  ws_setfifo (int /*<<< orphan*/ ) ; 
 TYPE_2__ wsconfig ; 

__attribute__((used)) static int
ws_openfifo_out (WSPipeOut * pipeout)
{
  int status = 0;

  ws_setfifo (wsconfig.pipeout);
  status = open (wsconfig.pipeout, O_WRONLY | O_NONBLOCK);
  /* will attempt on the next write */
  if (status == -1 && errno == ENXIO)
    LOG (("Unable to open fifo out: %s.\n", strerror (errno)));
  else if (status < 0)
    FATAL ("Unable to open fifo out: %s.", strerror (errno));
  pipeout->fd = status;

  if (status != -1 && status > max_file_fd)
    max_file_fd = status;

  return status;
}
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
typedef  TYPE_1__ WSPipeIn ;
struct TYPE_5__ {int /*<<< orphan*/  pipein; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  errno ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_setfifo (int /*<<< orphan*/ ) ; 
 TYPE_2__ wsconfig ; 

__attribute__((used)) static int
ws_openfifo_in (WSPipeIn * pipein)
{
  ws_setfifo (wsconfig.pipein);
  /* we should be able to open it at as reader */
  if ((pipein->fd = open (wsconfig.pipein, O_RDWR | O_NONBLOCK)) < 0)
    FATAL ("Unable to open fifo in: %s.", strerror (errno));

  return pipein->fd;
}
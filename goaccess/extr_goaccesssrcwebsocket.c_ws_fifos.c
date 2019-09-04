#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSServer ;
struct TYPE_7__ {int fd; } ;
typedef  TYPE_1__ WSPipeOut ;
struct TYPE_8__ {int fd; } ;
typedef  TYPE_2__ WSPipeIn ;
struct TYPE_9__ {int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 TYPE_6__ fdstate ; 
 int /*<<< orphan*/  handle_fifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_write_fifo (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ws_fifos (WSServer * server, WSPipeIn * pi, WSPipeOut * po)
{
  /* handle data via fifo */
  if (pi->fd != -1 && FD_ISSET (pi->fd, &fdstate.rfds))
    handle_fifo (server);
  /* handle data via fifo */
  if (po->fd != -1 && FD_ISSET (po->fd, &fdstate.wfds))
    ws_write_fifo (po, NULL, 0);
}
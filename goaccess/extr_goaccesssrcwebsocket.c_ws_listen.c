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
typedef  int /*<<< orphan*/  WSServer ;
struct TYPE_2__ {int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ fdstate ; 
 int /*<<< orphan*/  handle_accept (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_reads (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_writes (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ws_listen (int listener, int conn, WSServer * server)
{
  /* handle new connections */
  if (FD_ISSET (conn, &fdstate.rfds) && conn == listener)
    handle_accept (listener, server);
  /* handle data from a client */
  else if (FD_ISSET (conn, &fdstate.rfds) && conn != listener)
    handle_reads (conn, server);
  /* handle sending data to a client */
  else if (FD_ISSET (conn, &fdstate.wfds) && conn != listener)
    handle_writes (conn, server);
}
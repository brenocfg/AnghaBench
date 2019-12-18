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
struct TYPE_7__ {int closing; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_8__ {int status; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int WS_SENDING ; 
 int /*<<< orphan*/  handle_tcp_close (int,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
handle_read_close (int conn, WSClient * client, WSServer * server)
{
  if (client->status & WS_SENDING) {
    server->closing = 1;
    return;
  }
  handle_tcp_close (conn, client, server);
}
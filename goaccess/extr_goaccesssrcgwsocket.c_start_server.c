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
struct TYPE_5__ {int /*<<< orphan*/  self_pipe; int /*<<< orphan*/  onopen; } ;
struct TYPE_4__ {TYPE_2__* server; } ;
typedef  TYPE_1__ GWSWriter ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  onopen ; 
 int /*<<< orphan*/  set_self_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ws_start (TYPE_2__*) ; 
 int /*<<< orphan*/  ws_stop (TYPE_2__*) ; 

__attribute__((used)) static void
start_server (void *ptr_data)
{
  GWSWriter *writer = (GWSWriter *) ptr_data;

  writer->server->onopen = onopen;
  set_self_pipe (writer->server->self_pipe);

  /* select(2) will block in here */
  ws_start (writer->server);
  fprintf (stderr, "Stopping WebSocket server...\n");
  ws_stop (writer->server);
}
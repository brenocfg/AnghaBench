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
struct TYPE_6__ {scalar_t__ colist; int /*<<< orphan*/ * pipeout; int /*<<< orphan*/ * pipein; } ;
typedef  TYPE_1__ WSServer ;
typedef  int /*<<< orphan*/  WSPipeOut ;
typedef  int /*<<< orphan*/  WSPipeIn ;
struct TYPE_7__ {scalar_t__ accesslog; } ;

/* Variables and functions */
 int /*<<< orphan*/  access_log_close () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ list_count (scalar_t__) ; 
 int /*<<< orphan*/  list_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove_nodes (scalar_t__) ; 
 int /*<<< orphan*/  ws_clear_pipein (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_clear_pipeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_remove_dangling_clients ; 
 int /*<<< orphan*/  ws_ssl_cleanup (TYPE_1__*) ; 
 TYPE_2__ wsconfig ; 

void
ws_stop (WSServer * server)
{
  WSPipeIn **pipein = &server->pipein;
  WSPipeOut **pipeout = &server->pipeout;

  ws_clear_pipein (*pipein);
  ws_clear_pipeout (*pipeout);

  /* close access log (if any) */
  if (wsconfig.accesslog)
    access_log_close ();

  /* remove dangling clients */
  if (list_count (server->colist) > 0)
    list_foreach (server->colist, ws_remove_dangling_clients, NULL);

  if (server->colist)
    list_remove_nodes (server->colist);

#ifdef HAVE_LIBSSL
  ws_ssl_cleanup (server);
#endif

  free (server);
}
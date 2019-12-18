#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  colist; scalar_t__ closing; int /*<<< orphan*/  pipeout; int /*<<< orphan*/  (* onclose ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ WSServer ;
struct TYPE_15__ {int status; int /*<<< orphan*/ * ssl; int /*<<< orphan*/  end_proc; } ;
typedef  TYPE_2__ WSClient ;
struct TYPE_16__ {scalar_t__ accesslog; int /*<<< orphan*/  echomode; scalar_t__ strict; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int WS_ERR ; 
 int /*<<< orphan*/  access_log (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_ssl (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ws_clear_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  ws_close (int) ; 
 int /*<<< orphan*/  ws_free_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  ws_free_message (TYPE_2__*) ; 
 int /*<<< orphan*/  ws_remove_client_from_list (TYPE_2__*,TYPE_1__*) ; 
 TYPE_3__ wsconfig ; 

__attribute__((used)) static void
handle_tcp_close (int conn, WSClient * client, WSServer * server)
{
#ifdef HAVE_LIBSSL
  if (client->ssl)
    shutdown_ssl (client);
#endif

  shutdown (conn, SHUT_RDWR);
  /* upon close, call onclose() callback */
  if (server->onclose && wsconfig.strict && !wsconfig.echomode)
    (*server->onclose) (server->pipeout, client);

  /* do access logging */
  gettimeofday (&client->end_proc, NULL);
  if (wsconfig.accesslog)
    access_log (client, 200);

  /* errored out while parsing a frame or a message */
  if (client->status & WS_ERR) {
    ws_clear_queue (client);
    ws_free_frame (client);
    ws_free_message (client);
  }

  server->closing = 0;
  ws_close (conn);

#ifdef HAVE_LIBSSL
  if (client->ssl)
    SSL_free (client->ssl);
  client->ssl = NULL;
#endif

  /* remove client from our list */
  ws_remove_client_from_list (client, server);
  LOG (("Active: %d\n", list_count (server->colist)));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  colist; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_11__ {int status; int /*<<< orphan*/ * sockqueue; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int WS_SENDING ; 
 scalar_t__ handle_ssl_pending_rw (int,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  handle_write_close (int,TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* ws_get_client_from_list (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_respond (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_writes (int conn, WSServer * server)
{
  WSClient *client = NULL;

  if (!(client = ws_get_client_from_list (conn, &server->colist)))
    return;

#ifdef HAVE_LIBSSL
  if (handle_ssl_pending_rw (conn, server, client) == 0)
    return;
#endif

  ws_respond (client, NULL, 0); /* buffered data */
  /* done sending data */
  if (client->sockqueue == NULL)
    client->status &= ~WS_SENDING;

  /* An error ocurred while sending data or while reading data but still
   * waiting from the last send() from the server to the client.  e.g.,
   * sending status code */
  if ((client->status & WS_CLOSE) && !(client->status & WS_SENDING))
    handle_write_close (conn, client, server);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  colist; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_10__ {int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  sslstatus; } ;
typedef  TYPE_2__ WSClient ;
struct TYPE_11__ {scalar_t__ use_ssl; } ;

/* Variables and functions */
 int FD_SETSIZE ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  WS_TLS_ACCEPTING ; 
 int /*<<< orphan*/  WS_TOO_BUSY_STR ; 
 int accept_client (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_read_close (int,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  http_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ws_get_client_from_list (int,int /*<<< orphan*/ *) ; 
 TYPE_3__ wsconfig ; 

__attribute__((used)) static void
handle_accept (int listener, WSServer * server)
{
  WSClient *client = NULL;
  int newfd;

  newfd = accept_client (listener, &server->colist);
  if (newfd == -1)
    return;

  client = ws_get_client_from_list (newfd, &server->colist);
  if (newfd > FD_SETSIZE - 1) {
    LOG (("Too busy: %d %s.\n", newfd, client->remote_ip));

    http_error (client, WS_TOO_BUSY_STR);
    handle_read_close (newfd, client, server);
    return;
  }
#ifdef HAVE_LIBSSL
  /* set flag to do TLS handshake */
  if (wsconfig.use_ssl)
    client->sslstatus |= WS_TLS_ACCEPTING;
#endif

  LOG (("Accepted: %d %s\n", newfd, client->remote_ip));
}
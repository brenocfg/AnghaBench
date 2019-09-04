#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  colist; int /*<<< orphan*/  pipeout; int /*<<< orphan*/  (* onopen ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ WSServer ;
struct TYPE_18__ {int status; int /*<<< orphan*/  end_proc; TYPE_4__* headers; } ;
typedef  TYPE_2__ WSClient ;
struct TYPE_20__ {char* buf; int buflen; scalar_t__ reading; } ;
struct TYPE_19__ {scalar_t__ accesslog; int /*<<< orphan*/  echomode; scalar_t__ strict; } ;

/* Variables and functions */
 scalar_t__ BUFSIZ ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  WS_BAD_REQUEST_STR ; 
 int WS_CLOSE ; 
 int WS_OK ; 
 int WS_READING ; 
 int /*<<< orphan*/  access_log (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* new_wsheader () ; 
 scalar_t__ parse_headers (TYPE_4__*) ; 
 int read_socket (TYPE_2__*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ws_send_handshake_headers (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ws_set_handshake_headers (TYPE_4__*) ; 
 int ws_set_status (TYPE_2__*,int,int) ; 
 scalar_t__ ws_verify_req_headers (TYPE_4__*) ; 
 TYPE_3__ wsconfig ; 

__attribute__((used)) static int
ws_get_handshake (WSClient * client, WSServer * server)
{
  int bytes = 0, readh = 0;
  char *buf = NULL;

  if (client->headers == NULL)
    client->headers = new_wsheader ();

  buf = client->headers->buf;
  readh = client->headers->buflen;
  /* Probably the connection was closed before finishing handshake */
  if ((bytes = read_socket (client, buf + readh, BUFSIZ - readh)) < 1) {
    if (client->status & WS_CLOSE)
      http_error (client, WS_BAD_REQUEST_STR);
    return bytes;
  }
  client->headers->buflen += bytes;

  buf[client->headers->buflen] = '\0';  /* null-terminate */

  /* Must have a \r\n\r\n */
  if (strstr (buf, "\r\n\r\n") == NULL) {
    if (strlen (buf) < BUFSIZ)
      return ws_set_status (client, WS_READING, bytes);

    http_error (client, WS_BAD_REQUEST_STR);
    return ws_set_status (client, WS_CLOSE, bytes);
  }

  /* Ensure we have valid HTTP headers for the handshake */
  if (parse_headers (client->headers) != 0) {
    http_error (client, WS_BAD_REQUEST_STR);
    return ws_set_status (client, WS_CLOSE, bytes);
  }

  /* Ensure we have the required headers */
  if (ws_verify_req_headers (client->headers) != 0) {
    http_error (client, WS_BAD_REQUEST_STR);
    return ws_set_status (client, WS_CLOSE, bytes);
  }

  ws_set_handshake_headers (client->headers);

  /* handshake response */
  ws_send_handshake_headers (client, client->headers);

  /* upon success, call onopen() callback */
  if (server->onopen && wsconfig.strict && !wsconfig.echomode)
    server->onopen (server->pipeout, client);
  client->headers->reading = 0;

  /* do access logging */
  gettimeofday (&client->end_proc, NULL);
  if (wsconfig.accesslog)
    access_log (client, 101);
  LOG (("Active: %d\n", list_count (server->colist)));

  return ws_set_status (client, WS_OK, bytes);
}
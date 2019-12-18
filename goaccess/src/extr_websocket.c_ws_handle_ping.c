#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int payloadsz; char* payload; int /*<<< orphan*/  fragmented; scalar_t__ buflen; } ;
typedef  TYPE_1__ WSMessage ;
struct TYPE_9__ {int payloadlen; int /*<<< orphan*/  mask; int /*<<< orphan*/  fin; } ;
typedef  TYPE_2__ WSFrame ;
struct TYPE_10__ {int status; TYPE_1__* message; TYPE_2__* frame; } ;
typedef  TYPE_3__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int /*<<< orphan*/  WS_CLOSE_PROTO_ERR ; 
 int WS_ERR ; 
 int /*<<< orphan*/  WS_OPCODE_PONG ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  ws_free_message (TYPE_3__*) ; 
 int /*<<< orphan*/  ws_handle_err (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_send_frame (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ws_unmask_payload (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xcalloc (int,int) ; 

__attribute__((used)) static void
ws_handle_ping (WSClient * client)
{
  WSFrame **frm = &client->frame;
  WSMessage **msg = &client->message;
  char *buf = NULL, *tmp = NULL;
  int pos = 0, len = (*frm)->payloadlen, newlen = 0;

  /* RFC states that Control frames themselves MUST NOT be
   * fragmented. */
  if (!(*frm)->fin) {
    ws_handle_err (client, WS_CLOSE_PROTO_ERR, WS_ERR | WS_CLOSE, NULL);
    return;
  }

  /* Control frames are only allowed to have payload up to and
   * including 125 octets */
  if ((*frm)->payloadlen > 125) {
    ws_handle_err (client, WS_CLOSE_PROTO_ERR, WS_ERR | WS_CLOSE, NULL);
    return;
  }

  /* No payload from ping */
  if (len == 0) {
    ws_send_frame (client, WS_OPCODE_PONG, NULL, 0);
    return;
  }

  /* Copy the ping payload */
  pos = (*msg)->payloadsz - len;
  buf = xcalloc (len, sizeof (char));
  memcpy (buf, (*msg)->payload + pos, len);

  /* Unmask it */
  ws_unmask_payload (buf, len, 0, (*frm)->mask);

  /* Resize the current payload (keep an eye on this realloc) */
  newlen = (*msg)->payloadsz - len;
  tmp = realloc ((*msg)->payload, newlen);
  if (tmp == NULL && newlen > 0) {
    free ((*msg)->payload);
    free (buf);

    (*msg)->payload = NULL;
    client->status = WS_ERR | WS_CLOSE;
    return;
  }

  (*msg)->payload = tmp;
  (*msg)->payloadsz -= len;

  ws_send_frame (client, WS_OPCODE_PONG, buf, len);

  (*msg)->buflen = 0;   /* done with the current frame's payload */
  /* Control frame injected in the middle of a fragmented message. */
  if (!(*msg)->fragmented) {
    ws_free_message (client);
  }
  free (buf);
}
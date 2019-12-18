#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pipeout; int /*<<< orphan*/  (* onmessage ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
typedef  TYPE_1__ WSServer ;
struct TYPE_13__ {int mask_offset; int fragmented; scalar_t__ opcode; int /*<<< orphan*/  payloadsz; int /*<<< orphan*/  payload; scalar_t__ buflen; } ;
typedef  TYPE_2__ WSMessage ;
struct TYPE_14__ {scalar_t__ opcode; int /*<<< orphan*/  fin; int /*<<< orphan*/  mask; } ;
typedef  TYPE_3__ WSFrame ;
struct TYPE_15__ {int status; TYPE_2__* message; TYPE_3__* frame; } ;
typedef  TYPE_4__ WSClient ;
struct TYPE_16__ {int /*<<< orphan*/  strict; scalar_t__ echomode; } ;

/* Variables and functions */
 int WS_CLOSE ; 
 int /*<<< orphan*/  WS_CLOSE_INVALID_UTF8 ; 
 int WS_ERR ; 
 scalar_t__ WS_OPCODE_CONTINUATION ; 
 scalar_t__ WS_OPCODE_TEXT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ws_free_message (TYPE_4__*) ; 
 int /*<<< orphan*/  ws_handle_err (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_send_data (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_unmask_payload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ws_validate_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_write_fifo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ wsconfig ; 

__attribute__((used)) static void
ws_handle_text_bin (WSClient * client, WSServer * server)
{
  WSFrame **frm = &client->frame;
  WSMessage **msg = &client->message;
  int offset = (*msg)->mask_offset;

  /* All data frames after the initial data frame must have opcode 0 */
  if ((*msg)->fragmented && (*frm)->opcode != WS_OPCODE_CONTINUATION) {
    client->status = WS_ERR | WS_CLOSE;
    return;
  }

  /* RFC states that there is a new masking key per frame, therefore,
   * time to unmask... */
  ws_unmask_payload ((*msg)->payload, (*msg)->payloadsz, offset, (*frm)->mask);
  /* Done with the current frame's payload */
  (*msg)->buflen = 0;
  /* Reading a fragmented frame */
  (*msg)->fragmented = 1;

  if (!(*frm)->fin)
    return;

  /* validate text data encoded as UTF-8 */
  if ((*msg)->opcode == WS_OPCODE_TEXT) {
    if (ws_validate_string ((*msg)->payload, (*msg)->payloadsz) != 0) {
      ws_handle_err (client, WS_CLOSE_INVALID_UTF8, WS_ERR | WS_CLOSE, NULL);
      return;
    }
  }

  if ((*msg)->opcode != WS_OPCODE_CONTINUATION && server->onmessage) {
    /* just echo the message to the client */
    if (wsconfig.echomode)
      ws_send_data (client, (*msg)->opcode, (*msg)->payload, (*msg)->payloadsz);
    /* just pipe out the message */
    else if (!wsconfig.strict)
      ws_write_fifo (server->pipeout, (*msg)->payload, (*msg)->payloadsz);
    else
      server->onmessage (server->pipeout, client);
  }
  ws_free_message (client);
}
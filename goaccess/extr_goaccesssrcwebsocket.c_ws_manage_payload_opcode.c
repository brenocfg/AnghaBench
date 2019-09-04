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
typedef  int /*<<< orphan*/  WSServer ;
struct TYPE_9__ {int opcode; int /*<<< orphan*/  fragmented; } ;
typedef  TYPE_1__ WSMessage ;
struct TYPE_10__ {int opcode; } ;
typedef  TYPE_2__ WSFrame ;
struct TYPE_11__ {int status; TYPE_1__* message; TYPE_2__* frame; } ;
typedef  TYPE_3__ WSClient ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 int WS_CLOSE ; 
 int WS_ERR ; 
#define  WS_OPCODE_BIN 132 
#define  WS_OPCODE_CONTINUATION 131 
#define  WS_OPCODE_PING 130 
#define  WS_OPCODE_PONG 129 
#define  WS_OPCODE_TEXT 128 
 int /*<<< orphan*/  ws_handle_close (TYPE_3__*) ; 
 int /*<<< orphan*/  ws_handle_ping (TYPE_3__*) ; 
 int /*<<< orphan*/  ws_handle_pong (TYPE_3__*) ; 
 int /*<<< orphan*/  ws_handle_text_bin (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ws_manage_payload_opcode (WSClient * client, WSServer * server)
{
  WSFrame **frm = &client->frame;
  WSMessage **msg = &client->message;

  switch ((*frm)->opcode) {
  case WS_OPCODE_CONTINUATION:
    LOG (("CONTINUATION\n"));
    /* first frame can't be a continuation frame */
    if (!(*msg)->fragmented) {
      client->status = WS_ERR | WS_CLOSE;
      break;
    }
    ws_handle_text_bin (client, server);
    break;
  case WS_OPCODE_TEXT:
  case WS_OPCODE_BIN:
    LOG (("TEXT\n"));
    client->message->opcode = (*frm)->opcode;
    ws_handle_text_bin (client, server);
    break;
  case WS_OPCODE_PONG:
    LOG (("PONG\n"));
    ws_handle_pong (client);
    break;
  case WS_OPCODE_PING:
    LOG (("PING\n"));
    ws_handle_ping (client);
    break;
  default:
    LOG (("CLOSE\n"));
    ws_handle_close (client);
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* send_frame ) (TYPE_1__*,int,int,int,char const*,size_t) ;int /*<<< orphan*/  (* send_close ) (TYPE_1__*,int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 int /*<<< orphan*/  CLOSE_PROTOCOL_ERROR ; 
#define  OPCODE_BINARY 132 
#define  OPCODE_CLOSE 131 
#define  OPCODE_PING 130 
#define  OPCODE_PONG 129 
#define  OPCODE_TEXT 128 
 int /*<<< orphan*/  WS_ERROR ; 
 int /*<<< orphan*/  WS_SUCCESS ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int,int,char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int,int,char const*,size_t) ; 

ws_status on_frame(ws_t ws,
    bool is_fin, uint8_t opcode, bool is_masking,
    const char *payload_data, size_t payload_length,
    bool *to_keep) {
  switch (opcode) {
    case OPCODE_TEXT:
    case OPCODE_BINARY:
      if (!is_fin) {
        // wait for full data
        *to_keep = true;
        return WS_SUCCESS;
      }
      if (!is_masking) {
        return ws->send_close(ws, CLOSE_PROTOCOL_ERROR,
            "Clients must mask");
      }
      // echo
      return ws->send_frame(ws,
          true, opcode, false,
          payload_data, payload_length);

    case OPCODE_CLOSE:
      // ack close
      return ws->send_close(ws, CLOSE_NORMAL, NULL);

    case OPCODE_PING:
      // ack ping
      return ws->send_frame(ws,
          true, OPCODE_PONG, false,
          payload_data, payload_length);

    case OPCODE_PONG:
      return WS_SUCCESS;

    default:
      return WS_ERROR;
  }
}
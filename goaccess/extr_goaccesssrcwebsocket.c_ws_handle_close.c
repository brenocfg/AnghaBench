#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int WS_ERR ; 
 int /*<<< orphan*/  WS_OPCODE_CLOSE ; 
 int ws_send_frame (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ws_handle_close (WSClient * client)
{
  client->status = WS_ERR | WS_CLOSE;
  return ws_send_frame (client, WS_OPCODE_CLOSE, NULL, 0);
}
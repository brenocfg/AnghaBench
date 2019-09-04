#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;

/* Variables and functions */
 scalar_t__ h2o_is_websocket_handshake (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  h2o_upgrade_to_websocket (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_ws_message ; 

__attribute__((used)) static int on_req(h2o_handler_t *self, h2o_req_t *req)
{
    const char *client_key;

    if (h2o_is_websocket_handshake(req, &client_key) != 0 || client_key == NULL) {
        return -1;
    }
    h2o_upgrade_to_websocket(req, client_key, NULL, on_ws_message);
    return 0;
}
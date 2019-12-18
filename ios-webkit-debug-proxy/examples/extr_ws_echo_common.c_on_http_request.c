#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
typedef  TYPE_2__* my_t ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* send_data ) (TYPE_1__*,char*,int /*<<< orphan*/ ) ;scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_ERROR ; 
 int /*<<< orphan*/  WS_SUCCESS ; 
 char* create_root_response (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

ws_status on_http_request(ws_t ws,
    const char *method, const char *resource, const char *version,
    const char *host, const char *headers, size_t headers_length,
    bool is_websocket, bool *to_keep_alive) {
  if (strcmp(method, "GET") || strcmp(resource, "/")) {
    return WS_ERROR;
  }
  if (!is_websocket) {
    char *data = create_root_response(((my_t)ws->state)->port, 3);
    ws_status ret = ws->send_data(ws, data, strlen(data));
    free(data);
    return ret;
  }
  return WS_SUCCESS;
}
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
typedef  int /*<<< orphan*/  ws_t ;
typedef  int /*<<< orphan*/  ws_status ;

/* Variables and functions */
 int /*<<< orphan*/  iwdp_on_devtools_request (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  iwdp_on_list_request (int /*<<< orphan*/ ,int,int,char const*) ; 
 int /*<<< orphan*/  iwdp_on_not_found (int /*<<< orphan*/ ,int,char const*,char*) ; 
 int /*<<< orphan*/  iwdp_on_static_request (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

ws_status iwdp_on_http_request(ws_t ws,
    const char *method, const char *resource, const char *version,
    const char *host, const char *headers, size_t headers_length,
    bool is_websocket, bool *to_keep_alive) {
  bool is_get = !strcmp(method, "GET");
  bool is_head = !is_get && !strcmp(method, "HEAD");
  if (is_websocket) {
    if (is_get && !strncmp(resource, "/devtools/page/", 15)) {
      return iwdp_on_devtools_request(ws, resource);
    }
  } else {
    if (!is_get && !is_head) {
      return iwdp_on_not_found(ws, is_head, resource, "Method Not Allowed");
    }

    if (!strlen(resource) || !strcmp(resource, "/")) {
      return iwdp_on_list_request(ws, is_head, false, host);
    } else if (!strcmp(resource, "/json") || !strcmp(resource, "/json/list")) {
      return iwdp_on_list_request(ws, is_head, true, host);
    } else if (!strncmp(resource, "/devtools/", 10)) {
      return iwdp_on_static_request(ws, is_head, resource,
          to_keep_alive);
    }
    // Chrome's devtools_http_handler_impl.cc also supports:
    //   /json/version*  -- version info
    //   /json/new*      -- open page
    //   /json/close/*   -- close page
    //   /thumb/*        -- get page thumbnail png
  }
  return iwdp_on_not_found(ws, is_head, resource, NULL);
}
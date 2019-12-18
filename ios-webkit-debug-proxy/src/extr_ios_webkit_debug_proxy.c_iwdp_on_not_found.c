#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
struct TYPE_5__ {int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  iwdp_send_http (TYPE_1__*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

ws_status iwdp_on_not_found(ws_t ws, bool is_head, const char *resource,
    const char *details) {
  char *content;
  if (asprintf(&content,
      "<html><title>Error 404 (Not Found)</title>\n"
      "<p><b>404.</b> <ins>That's an error.</ins>\n"
      "<p>The requested URL <code>%s</code> was not found.\n"
      "%s</html>", resource, (details ? details : "")) < 0) {
    return ws->on_error(ws, "asprintf failed");
  }
  ws_status ret = iwdp_send_http(ws, is_head, "404 Not Found", ".html",
      content);
  free(content);
  return ret;
}
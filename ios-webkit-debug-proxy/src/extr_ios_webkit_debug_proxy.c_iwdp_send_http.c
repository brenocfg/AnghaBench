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
struct TYPE_5__ {int /*<<< orphan*/  (* send_data ) (TYPE_1__*,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  iwdp_get_content_type (char const*,int,char**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

ws_status iwdp_send_http(ws_t ws, bool is_head, const char *status,
    const char *resource, const char *content) {
  char *ctype;
  iwdp_get_content_type(resource, false, &ctype);
  char *data;
  if (asprintf(&data,
      "HTTP/1.1 %s\r\n"
      "Content-length: %zd\r\n"
      "Connection: close"
      "%s%s\r\n\r\n%s",
      status, (content ? strlen(content) : 0),
      (ctype ? "\r\nContent-Type: " : ""), (ctype ? ctype : ""),
      (content && !is_head ? content : "")) < 0) {
    return ws->on_error(ws, "asprintf failed");
  }
  free(ctype);
  ws_status ret = ws->send_data(ws, data, strlen(data));
  free(data);
  return ret;
}
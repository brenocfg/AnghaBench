#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
typedef  TYPE_3__* ws_private_t ;
struct TYPE_9__ {char* method; char* resource; char* http_version; TYPE_1__* in; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* on_error ) (TYPE_2__*,char*) ;TYPE_3__* private_state; } ;
struct TYPE_7__ {char* in_head; char const* in_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_SUCCESS ; 
 char* strndup (char const*,int) ; 
 char* strnstr (char const*,char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*) ; 

ws_status ws_read_http_request(ws_t self) {
  ws_private_t my = self->private_state;
  const char *in_head = my->in->in_head;
  size_t in_length = my->in->in_tail - in_head;

  char *line_end = strnstr(in_head, "\r\n", in_length);
  if (!line_end) {
    return self->on_error(self, "Missing \\r\\n");
  }

  char *trio[3];
  size_t i;
  for (i = 0; i < 3; i++) {
    while (in_head < line_end && *in_head == ' ') {
      in_head++;
    }
    const char *s = in_head;
    while (in_head < line_end && *in_head != ' ') {
      in_head++;
    }
    trio[i] = (s < in_head ? strndup(s, in_head - s) : NULL);
  }
  my->method = trio[0];
  my->resource = trio[1];
  my->http_version = trio[2];

  // Keep the request tail '\r\n', in case our client doesn't send
  // any headers, so ws_recv_headers can simply check for "\r\n\r\n".
  my->in->in_head = line_end;
  if (!my->http_version) {
    return self->on_error(self, "Invalid HTTP header");
  }
  return WS_SUCCESS;
}
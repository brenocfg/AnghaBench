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
struct TYPE_4__ {int type; int /*<<< orphan*/  http_errno; int /*<<< orphan*/  state; void* data; } ;
typedef  TYPE_1__ http_parser ;
typedef  enum http_parser_type { ____Placeholder_http_parser_type } http_parser_type ;

/* Variables and functions */
 int /*<<< orphan*/  HPE_OK ; 
 int HTTP_REQUEST ; 
 int HTTP_RESPONSE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_start_req ; 
 int /*<<< orphan*/  s_start_req_or_res ; 
 int /*<<< orphan*/  s_start_res ; 

void
http_parser_init (http_parser *parser, enum http_parser_type t)
{
  void *data = parser->data; /* preserve application data */
  memset(parser, 0, sizeof(*parser));
  parser->data = data;
  parser->type = t;
  parser->state = (t == HTTP_REQUEST ? s_start_req : (t == HTTP_RESPONSE ? s_start_res : s_start_req_or_res));
  parser->http_errno = HPE_OK;
}
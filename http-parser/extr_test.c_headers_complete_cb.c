#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  http_minor; int /*<<< orphan*/  http_major; int /*<<< orphan*/  status_code; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ http_parser ;
struct TYPE_7__ {int /*<<< orphan*/  should_keep_alive; int /*<<< orphan*/  headers_complete_cb_called; int /*<<< orphan*/  http_minor; int /*<<< orphan*/  http_major; int /*<<< orphan*/  status_code; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  http_should_keep_alive (TYPE_1__*) ; 
 TYPE_3__* messages ; 
 size_t num_messages ; 
 TYPE_1__ parser ; 

int
headers_complete_cb (http_parser *p)
{
  assert(p == &parser);
  messages[num_messages].method = parser.method;
  messages[num_messages].status_code = parser.status_code;
  messages[num_messages].http_major = parser.http_major;
  messages[num_messages].http_minor = parser.http_minor;
  messages[num_messages].headers_complete_cb_called = TRUE;
  messages[num_messages].should_keep_alive = http_should_keep_alive(&parser);
  return 0;
}
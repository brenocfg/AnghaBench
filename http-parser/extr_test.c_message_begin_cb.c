#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  http_parser ;
struct TYPE_2__ {scalar_t__ message_begin_cb_called; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* messages ; 
 size_t num_messages ; 
 int /*<<< orphan*/  parser ; 

int
message_begin_cb (http_parser *p)
{
  assert(p == &parser);
  assert(!messages[num_messages].message_begin_cb_called);
  messages[num_messages].message_begin_cb_called = TRUE;
  return 0;
}
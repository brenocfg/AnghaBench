#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  events; int /*<<< orphan*/  poll_handle; int /*<<< orphan*/  delayed_events; } ;
typedef  TYPE_2__ connection_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  connection_poll_cb ; 
 scalar_t__ uv_is_active (int /*<<< orphan*/ *) ; 
 int uv_poll_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delay_timer_cb(uv_timer_t* timer) {
  connection_context_t* context = (connection_context_t*) timer->data;
  int r;

  /* Timer should auto stop. */
  ASSERT(0 == uv_is_active((uv_handle_t*) timer));

  /* Add the requested events to the poll mask. */
  ASSERT(context->delayed_events != 0);
  context->events |= context->delayed_events;
  context->delayed_events = 0;

  r = uv_poll_start(&context->poll_handle,
                    context->events,
                    connection_poll_cb);
  ASSERT(r == 0);
}
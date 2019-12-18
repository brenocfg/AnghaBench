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
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  connection_cb_called ; 
 int /*<<< orphan*/  incoming ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timer_cb ; 
 scalar_t__ uv_accept (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* tcp, int status) {
  ASSERT(status == 0);

  ASSERT(0 == uv_tcp_init(tcp->loop, &incoming));
  ASSERT(0 == uv_accept(tcp, (uv_stream_t*) &incoming));

  ASSERT(0 == uv_timer_init(uv_default_loop(), &timer));
  ASSERT(0 == uv_timer_start(&timer, timer_cb, 1000, 0));

  connection_cb_called++;
}
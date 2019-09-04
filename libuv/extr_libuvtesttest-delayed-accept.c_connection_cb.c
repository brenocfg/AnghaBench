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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ uv_timer_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  connection_cb_called ; 
 int /*<<< orphan*/  do_accept ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_timer_init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int uv_timer_start (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* tcp, int status) {
  int r;
  uv_timer_t* timer_handle;

  ASSERT(status == 0);

  timer_handle = (uv_timer_t*)malloc(sizeof *timer_handle);
  ASSERT(timer_handle != NULL);

  /* Accept the client after 1 second */
  r = uv_timer_init(uv_default_loop(), timer_handle);
  ASSERT(r == 0);

  timer_handle->data = tcp;

  r = uv_timer_start(timer_handle, do_accept, 1000, 0);
  ASSERT(r == 0);

  connection_cb_called++;
}
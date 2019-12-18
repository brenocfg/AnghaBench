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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 TYPE_1__ ctx2 ; 
 int /*<<< orphan*/  read_cb ; 
 scalar_t__ uv_is_closing (int /*<<< orphan*/ *) ; 
 int uv_is_readable (int /*<<< orphan*/ *) ; 
 int uv_is_writable (int /*<<< orphan*/ *) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_recv_start(void) {
  int r;
  ASSERT(1 == uv_is_readable((uv_stream_t*)&ctx2.channel));
  ASSERT(1 == uv_is_writable((uv_stream_t*)&ctx2.channel));
  ASSERT(0 == uv_is_closing((uv_handle_t*)&ctx2.channel));

  r = uv_read_start((uv_stream_t*)&ctx2.channel, alloc_cb, read_cb);
  ASSERT(r == 0);
}
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
struct TYPE_2__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  listen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__ ctx2 ; 
 int /*<<< orphan*/  send_recv_start () ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void listen_cb(uv_stream_t* handle, int status) {
  int r;
  ASSERT(handle == (uv_stream_t*)&ctx2.listen);
  ASSERT(status == 0);

  r = uv_accept((uv_stream_t*)&ctx2.listen, (uv_stream_t*)&ctx2.channel);
  ASSERT(r == 0);

  send_recv_start();
}
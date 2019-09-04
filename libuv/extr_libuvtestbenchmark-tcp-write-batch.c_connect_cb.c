#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  req; } ;
typedef  TYPE_1__ write_req ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_2__ uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NUM_WRITE_REQS ; 
 int /*<<< orphan*/  connect_cb_called ; 
 int /*<<< orphan*/  shutdown_cb ; 
 int /*<<< orphan*/  shutdown_req ; 
 int /*<<< orphan*/  tcp_client ; 
 int uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 TYPE_1__* write_reqs ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  write_req* w;
  int i;
  int r;

  ASSERT(req->handle == (uv_stream_t*)&tcp_client);

  for (i = 0; i < NUM_WRITE_REQS; i++) {
    w = &write_reqs[i];
    r = uv_write(&w->req, req->handle, &w->buf, 1, write_cb);
    ASSERT(r == 0);
  }

  r = uv_shutdown(&shutdown_req, req->handle, shutdown_cb);
  ASSERT(r == 0);

  connect_cb_called++;
}
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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {TYPE_2__* handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  pinger_t ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  pinger_on_connect_count ; 
 int /*<<< orphan*/  pinger_read_cb ; 
 int /*<<< orphan*/  pinger_write_ping (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_is_closing (int /*<<< orphan*/ *) ; 
 int uv_is_readable (TYPE_2__*) ; 
 int uv_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pinger_on_connect(uv_connect_t *req, int status) {
  pinger_t *pinger = (pinger_t*)req->handle->data;

  pinger_on_connect_count++;

  ASSERT(status == 0);

  ASSERT(1 == uv_is_readable(req->handle));
  ASSERT(1 == uv_is_writable(req->handle));
  ASSERT(0 == uv_is_closing((uv_handle_t *) req->handle));

  pinger_write_ping(pinger);

  uv_read_start((uv_stream_t*)(req->handle), alloc_cb, pinger_read_cb);
}
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
struct TYPE_4__ {TYPE_2__* handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  pinger_t ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  buf_alloc ; 
 int /*<<< orphan*/  pinger_read_cb ; 
 int /*<<< orphan*/  pinger_write_ping (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_read_start (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pinger_connect_cb(uv_connect_t* req, int status) {
  pinger_t *pinger = (pinger_t*)req->handle->data;

  ASSERT(status == 0);

  pinger_write_ping(pinger);

  if (uv_read_start(req->handle, buf_alloc, pinger_read_cb)) {
    FATAL("uv_read_start failed");
  }
}
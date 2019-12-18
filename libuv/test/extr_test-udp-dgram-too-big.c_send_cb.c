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
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ uv_udp_send_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK_HANDLE (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_REQ (TYPE_1__*) ; 
 int UV_EMSGSIZE ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  send_cb_called ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_cb(uv_udp_send_t* req, int status) {
  CHECK_REQ(req);
  CHECK_HANDLE(req->handle);

  ASSERT(status == UV_EMSGSIZE);

  uv_close((uv_handle_t*)req->handle, close_cb);
  send_cb_called++;
}
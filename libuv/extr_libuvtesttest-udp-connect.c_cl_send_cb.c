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
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ uv_udp_send_t ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK_HANDLE (int /*<<< orphan*/ ) ; 
 int UV_EDESTADDRREQ ; 
 int /*<<< orphan*/  buf ; 
 int cl_send_cb_called ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  lo_addr ; 
 int /*<<< orphan*/  uv_udp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_udp_send (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct sockaddr const*,void (*) (TYPE_1__*,int)) ; 

__attribute__((used)) static void cl_send_cb(uv_udp_send_t* req, int status) {
  int r;

  ASSERT(req != NULL);
  ASSERT(status == 0);
  CHECK_HANDLE(req->handle);
  if (++cl_send_cb_called == 1) {
    uv_udp_connect(&client, NULL);
    r = uv_udp_send(req, &client, &buf, 1, NULL, cl_send_cb);
    ASSERT(r == UV_EDESTADDRREQ);
    r = uv_udp_send(req,
                    &client,
                    &buf,
                    1,
                    (const struct sockaddr*) &lo_addr,
                    cl_send_cb);
    ASSERT(r == 0);
  }

}
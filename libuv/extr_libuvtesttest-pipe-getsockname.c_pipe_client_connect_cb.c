#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PIPENAME ; 
 int /*<<< orphan*/  connect_req ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pipe_client ; 
 int /*<<< orphan*/  pipe_client_connect_cb_called ; 
 int /*<<< orphan*/  pipe_close_cb ; 
 int /*<<< orphan*/  pipe_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_pipe_getpeername (int /*<<< orphan*/ *,char*,size_t*) ; 
 int uv_pipe_getsockname (int /*<<< orphan*/ *,char*,size_t*) ; 

__attribute__((used)) static void pipe_client_connect_cb(uv_connect_t* req, int status) {
  char buf[1024];
  size_t len;
  int r;

  ASSERT(req == &connect_req);
  ASSERT(status == 0);

  len = sizeof buf;
  r = uv_pipe_getpeername(&pipe_client, buf, &len);
  ASSERT(r == 0);

  ASSERT(buf[len - 1] != 0);
  ASSERT(memcmp(buf, TEST_PIPENAME, len) == 0);

  len = sizeof buf;
  r = uv_pipe_getsockname(&pipe_client, buf, &len);
  ASSERT(r == 0 && len == 0);

  pipe_client_connect_cb_called++;


  uv_close((uv_handle_t*) &pipe_client, pipe_close_cb);
  uv_close((uv_handle_t*) &pipe_server, pipe_close_cb);
}
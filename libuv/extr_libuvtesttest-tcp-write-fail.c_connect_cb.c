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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connect_cb_called ; 
 TYPE_1__ connect_req ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  uv_buf_t buf;
  uv_stream_t* stream;
  int r;

  ASSERT(req == &connect_req);
  ASSERT(status == 0);

  stream = req->handle;
  connect_cb_called++;

  /* close the socket, the hard way */
  close_socket((uv_tcp_t*)stream);

  buf = uv_buf_init("hello\n", 6);
  r = uv_write(&write_req, stream, &buf, 1, write_cb);
  ASSERT(r == 0);
}
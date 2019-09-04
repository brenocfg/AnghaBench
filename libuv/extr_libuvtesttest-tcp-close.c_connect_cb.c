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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NUM_WRITE_REQS ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  tcp_handle ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 

__attribute__((used)) static void connect_cb(uv_connect_t* conn_req, int status) {
  uv_write_t* req;
  uv_buf_t buf;
  int i, r;

  buf = uv_buf_init("PING", 4);
  for (i = 0; i < NUM_WRITE_REQS; i++) {
    req = malloc(sizeof *req);
    ASSERT(req != NULL);

    r = uv_write(req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
    ASSERT(r == 0);
  }

  uv_close((uv_handle_t*)&tcp_handle, close_cb);
}
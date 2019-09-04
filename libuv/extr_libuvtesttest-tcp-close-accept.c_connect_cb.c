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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/ * connect_reqs ; 
 size_t pending_incoming ; 
 int /*<<< orphan*/  tcp_check ; 
 int /*<<< orphan*/  tcp_check_req ; 
 int /*<<< orphan*/ * tcp_incoming ; 
 int /*<<< orphan*/ * tcp_outgoing ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 int /*<<< orphan*/ * write_reqs ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  unsigned int i;
  uv_buf_t buf;
  uv_stream_t* outgoing;

  if (req == &tcp_check_req) {
    ASSERT(status != 0);

    /*
     * Time to finish the test: close both the check and pending incoming
     * connections
     */
    uv_close((uv_handle_t*) &tcp_incoming[pending_incoming], close_cb);
    uv_close((uv_handle_t*) &tcp_check, close_cb);
    return;
  }

  ASSERT(status == 0);
  ASSERT(connect_reqs <= req);
  ASSERT(req <= connect_reqs + ARRAY_SIZE(connect_reqs));
  i = req - connect_reqs;

  buf = uv_buf_init("x", 1);
  outgoing = (uv_stream_t*) &tcp_outgoing[i];
  ASSERT(0 == uv_write(&write_reqs[i], outgoing, &buf, 1, write_cb));
}
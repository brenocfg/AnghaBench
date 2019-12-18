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
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  buf_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  nrecv ; 
 scalar_t__ nrecv_total ; 
 int /*<<< orphan*/  read_sockets_close_cb ; 
 scalar_t__ start_time ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_cb(uv_stream_t* stream, ssize_t bytes, const uv_buf_t* buf) {
  if (nrecv_total == 0) {
    ASSERT(start_time == 0);
    uv_update_time(loop);
    start_time = uv_now(loop);
  }

  if (bytes < 0) {
    uv_close((uv_handle_t*)stream, read_sockets_close_cb);
    return;
  }

  buf_free(buf);

  nrecv += bytes;
  nrecv_total += bytes;
}
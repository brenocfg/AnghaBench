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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_EOF ; 
 int read_cb_called ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_read_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_cb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf) {
  switch (++read_cb_called) {
  case 1:
    ASSERT(nread == 1);
    uv_read_stop(handle);
    break;
  case 2:
    ASSERT(nread == UV_EOF);
    uv_close((uv_handle_t *) handle, NULL);
    break;
  default:
    ASSERT(!"read_cb_called > 2");
  }
}
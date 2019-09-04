#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EOF ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_cb(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
  /* The server will not send anything, it should close gracefully. */

  if (buf->base) {
    free(buf->base);
  }

  if (nread >= 0) {
    ASSERT(nread == 0);
  } else {
    ASSERT(tcp != NULL);
    ASSERT(nread == UV_EOF);
    uv_close((uv_handle_t*)tcp, close_cb);
  }
}
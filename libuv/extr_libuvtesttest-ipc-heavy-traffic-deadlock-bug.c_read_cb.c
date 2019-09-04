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
struct TYPE_3__ {scalar_t__* base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BUFFER_CONTENT ; 
 scalar_t__ XFER_SIZE ; 
 scalar_t__ bytes_read ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  shutdown_cb ; 
 int /*<<< orphan*/  shutdown_req ; 
 int uv_read_stop (int /*<<< orphan*/ *) ; 
 int uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  ssize_t i;
  int r;

  ASSERT(nread >= 0);
  bytes_read += nread;

  for (i = 0; i < nread; i++)
    ASSERT(buf->base[i] == BUFFER_CONTENT);
  free(buf->base);

  if (bytes_read >= XFER_SIZE) {
    r = uv_read_stop(handle);
    ASSERT(r == 0);
    r = uv_shutdown(&shutdown_req, handle, shutdown_cb);
    ASSERT(r == 0);
  }
}
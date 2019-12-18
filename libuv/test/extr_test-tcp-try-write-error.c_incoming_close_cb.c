#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct TYPE_2__ {scalar_t__ write_queue_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_ECONNABORTED ; 
 int UV_ECONNRESET ; 
 int UV_EPIPE ; 
 TYPE_1__ client ; 
 int /*<<< orphan*/  close_cb_called ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 char* uv_strerror (int) ; 
 int uv_try_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void incoming_close_cb(uv_handle_t* handle) {
  uv_buf_t buf;
  int r = 1;

  close_cb_called++;

  buf = uv_buf_init("meow", 4);
  while (r > 0)
    r = uv_try_write((uv_stream_t*) &client, &buf, 1);
  fprintf(stderr, "uv_try_write error: %d %s\n", r, uv_strerror(r));
  ASSERT(r == UV_EPIPE || r == UV_ECONNABORTED || r == UV_ECONNRESET);
  ASSERT(client.write_queue_size == 0);
}
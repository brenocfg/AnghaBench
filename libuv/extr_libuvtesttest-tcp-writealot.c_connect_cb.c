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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CHUNKS_PER_WRITE ; 
 scalar_t__ CHUNK_SIZE ; 
 int WRITES ; 
 int /*<<< orphan*/  alloc_cb ; 
 scalar_t__ bytes_sent ; 
 int /*<<< orphan*/  connect_cb_called ; 
 TYPE_1__ connect_req ; 
 int /*<<< orphan*/  read_cb ; 
 scalar_t__ send_buffer ; 
 int /*<<< orphan*/  shutdown_cb ; 
 int /*<<< orphan*/  shutdown_req ; 
 int /*<<< orphan*/  uv_buf_init (scalar_t__,scalar_t__) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 int /*<<< orphan*/ * write_reqs ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  uv_buf_t send_bufs[CHUNKS_PER_WRITE];
  uv_stream_t* stream;
  int i, j, r;

  ASSERT(req == &connect_req);
  ASSERT(status == 0);

  stream = req->handle;
  connect_cb_called++;

  /* Write a lot of data */
  for (i = 0; i < WRITES; i++) {
    uv_write_t* write_req = write_reqs + i;

    for (j = 0; j < CHUNKS_PER_WRITE; j++) {
      send_bufs[j] = uv_buf_init(send_buffer + bytes_sent, CHUNK_SIZE);
      bytes_sent += CHUNK_SIZE;
    }

    r = uv_write(write_req, stream, send_bufs, CHUNKS_PER_WRITE, write_cb);
    ASSERT(r == 0);
  }

  /* Shutdown on drain. */
  r = uv_shutdown(&shutdown_req, stream, shutdown_cb);
  ASSERT(r == 0);

  /* Start reading */
  r = uv_read_start(stream, alloc_cb, read_cb);
  ASSERT(r == 0);
}
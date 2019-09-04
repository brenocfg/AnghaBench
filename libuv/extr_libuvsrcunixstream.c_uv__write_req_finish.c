#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ error; int /*<<< orphan*/  queue; int /*<<< orphan*/ * bufs; int /*<<< orphan*/ * bufsml; TYPE_2__* handle; } ;
typedef  TYPE_1__ uv_write_t ;
struct TYPE_5__ {int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  write_completed_queue; } ;
typedef  TYPE_2__ uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__io_feed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__write_req_finish(uv_write_t* req) {
  uv_stream_t* stream = req->handle;

  /* Pop the req off tcp->write_queue. */
  QUEUE_REMOVE(&req->queue);

  /* Only free when there was no error. On error, we touch up write_queue_size
   * right before making the callback. The reason we don't do that right away
   * is that a write_queue_size > 0 is our only way to signal to the user that
   * they should stop writing - which they should if we got an error. Something
   * to revisit in future revisions of the libuv API.
   */
  if (req->error == 0) {
    if (req->bufs != req->bufsml)
      uv__free(req->bufs);
    req->bufs = NULL;
  }

  /* Add it to the write_completed_queue where it will have its
   * callback called in the near future.
   */
  QUEUE_INSERT_TAIL(&stream->write_completed_queue, &req->queue);
  uv__io_feed(stream->loop, &stream->io_watcher);
}
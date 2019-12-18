#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int nbufs; int /*<<< orphan*/  queue; scalar_t__ write_index; int /*<<< orphan*/ * bufs; int /*<<< orphan*/ * bufsml; TYPE_2__* send_handle; scalar_t__ error; TYPE_2__* handle; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ uv_write_t ;
typedef  int /*<<< orphan*/  uv_write_cb ;
struct TYPE_12__ {scalar_t__ type; int flags; scalar_t__ write_queue_size; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; scalar_t__ connect_req; int /*<<< orphan*/  write_queue; } ;
typedef  TYPE_2__ uv_stream_t ;
struct TYPE_13__ {int /*<<< orphan*/  ipc; } ;
typedef  TYPE_3__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  int /*<<< orphan*/  bufs ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UV_EBADF ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV_ENOSYS ; 
 int UV_EPIPE ; 
 int UV_HANDLE_BLOCKING_WRITES ; 
 int UV_HANDLE_WRITABLE ; 
 scalar_t__ UV_NAMED_PIPE ; 
 scalar_t__ UV_TCP ; 
 scalar_t__ UV_TTY ; 
 int /*<<< orphan*/  UV_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ uv__count_bufs (int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ uv__handle_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uv__malloc (unsigned int) ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__stream_fd (TYPE_2__*) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_2__*) ; 
 int /*<<< orphan*/  uv__write (TYPE_2__*) ; 

int uv_write2(uv_write_t* req,
              uv_stream_t* stream,
              const uv_buf_t bufs[],
              unsigned int nbufs,
              uv_stream_t* send_handle,
              uv_write_cb cb) {
  int empty_queue;

  assert(nbufs > 0);
  assert((stream->type == UV_TCP ||
          stream->type == UV_NAMED_PIPE ||
          stream->type == UV_TTY) &&
         "uv_write (unix) does not yet support other types of streams");

  if (uv__stream_fd(stream) < 0)
    return UV_EBADF;

  if (!(stream->flags & UV_HANDLE_WRITABLE))
    return UV_EPIPE;

  if (send_handle) {
    if (stream->type != UV_NAMED_PIPE || !((uv_pipe_t*)stream)->ipc)
      return UV_EINVAL;

    /* XXX We abuse uv_write2() to send over UDP handles to child processes.
     * Don't call uv__stream_fd() on those handles, it's a macro that on OS X
     * evaluates to a function that operates on a uv_stream_t with a couple of
     * OS X specific fields. On other Unices it does (handle)->io_watcher.fd,
     * which works but only by accident.
     */
    if (uv__handle_fd((uv_handle_t*) send_handle) < 0)
      return UV_EBADF;

#if defined(__CYGWIN__) || defined(__MSYS__)
    /* Cygwin recvmsg always sets msg_controllen to zero, so we cannot send it.
       See https://github.com/mirror/newlib-cygwin/blob/86fc4bf0/winsup/cygwin/fhandler_socket.cc#L1736-L1743 */
    return UV_ENOSYS;
#endif
  }

  /* It's legal for write_queue_size > 0 even when the write_queue is empty;
   * it means there are error-state requests in the write_completed_queue that
   * will touch up write_queue_size later, see also uv__write_req_finish().
   * We could check that write_queue is empty instead but that implies making
   * a write() syscall when we know that the handle is in error mode.
   */
  empty_queue = (stream->write_queue_size == 0);

  /* Initialize the req */
  uv__req_init(stream->loop, req, UV_WRITE);
  req->cb = cb;
  req->handle = stream;
  req->error = 0;
  req->send_handle = send_handle;
  QUEUE_INIT(&req->queue);

  req->bufs = req->bufsml;
  if (nbufs > ARRAY_SIZE(req->bufsml))
    req->bufs = uv__malloc(nbufs * sizeof(bufs[0]));

  if (req->bufs == NULL)
    return UV_ENOMEM;

  memcpy(req->bufs, bufs, nbufs * sizeof(bufs[0]));
  req->nbufs = nbufs;
  req->write_index = 0;
  stream->write_queue_size += uv__count_bufs(bufs, nbufs);

  /* Append the request to write_queue. */
  QUEUE_INSERT_TAIL(&stream->write_queue, &req->queue);

  /* If the queue was empty when this function began, we should attempt to
   * do the write immediately. Otherwise start the write_watcher and wait
   * for the fd to become writable.
   */
  if (stream->connect_req) {
    /* Still connecting, do nothing. */
  }
  else if (empty_queue) {
    uv__write(stream);
  }
  else {
    /*
     * blocking streams should never have anything in the queue.
     * if this assert fires then somehow the blocking stream isn't being
     * sufficiently flushed in uv__write.
     */
    assert(!(stream->flags & UV_HANDLE_BLOCKING_WRITES));
    uv__io_start(stream->loop, &stream->io_watcher, POLLOUT);
    uv__stream_osx_interrupt_select(stream);
  }

  return 0;
}
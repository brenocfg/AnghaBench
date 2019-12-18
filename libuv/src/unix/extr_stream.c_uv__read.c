#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int flags; scalar_t__ type; int /*<<< orphan*/  (* read_cb ) (TYPE_1__*,scalar_t__,TYPE_3__*) ;int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  (* alloc_cb ) (int /*<<< orphan*/ *,int,TYPE_3__*) ;} ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_26__ {scalar_t__ ipc; } ;
typedef  TYPE_2__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_27__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_3__ uv_buf_t ;
struct msghdr {int msg_iovlen; int msg_controllen; char* msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; scalar_t__ msg_flags; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  cmsg_space ;

/* Variables and functions */
 int CMSG_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ ECONNRESET ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int UV_DISCONNECT ; 
 int UV_ENOBUFS ; 
 int UV_HANDLE_READING ; 
 int UV_HANDLE_READ_PARTIAL ; 
 scalar_t__ UV_NAMED_PIPE ; 
 int /*<<< orphan*/  UV__CMSG_FD_SIZE ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ read (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* uv__recvmsg (scalar_t__,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stream_eof (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ uv__stream_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_1__*) ; 
 int uv__stream_recv_cmsg (TYPE_1__*,struct msghdr*) ; 
 TYPE_3__ uv_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv__read(uv_stream_t* stream) {
  uv_buf_t buf;
  ssize_t nread;
  struct msghdr msg;
  char cmsg_space[CMSG_SPACE(UV__CMSG_FD_SIZE)];
  int count;
  int err;
  int is_ipc;

  stream->flags &= ~UV_HANDLE_READ_PARTIAL;

  /* Prevent loop starvation when the data comes in as fast as (or faster than)
   * we can read it. XXX Need to rearm fd if we switch to edge-triggered I/O.
   */
  count = 32;

  is_ipc = stream->type == UV_NAMED_PIPE && ((uv_pipe_t*) stream)->ipc;

  /* XXX: Maybe instead of having UV_HANDLE_READING we just test if
   * tcp->read_cb is NULL or not?
   */
  while (stream->read_cb
      && (stream->flags & UV_HANDLE_READING)
      && (count-- > 0)) {
    assert(stream->alloc_cb != NULL);

    buf = uv_buf_init(NULL, 0);
    stream->alloc_cb((uv_handle_t*)stream, 64 * 1024, &buf);
    if (buf.base == NULL || buf.len == 0) {
      /* User indicates it can't or won't handle the read. */
      stream->read_cb(stream, UV_ENOBUFS, &buf);
      return;
    }

    assert(buf.base != NULL);
    assert(uv__stream_fd(stream) >= 0);

    if (!is_ipc) {
      do {
        nread = read(uv__stream_fd(stream), buf.base, buf.len);
      }
      while (nread < 0 && errno == EINTR);
    } else {
      /* ipc uses recvmsg */
      msg.msg_flags = 0;
      msg.msg_iov = (struct iovec*) &buf;
      msg.msg_iovlen = 1;
      msg.msg_name = NULL;
      msg.msg_namelen = 0;
      /* Set up to receive a descriptor even if one isn't in the message */
      msg.msg_controllen = sizeof(cmsg_space);
      msg.msg_control = cmsg_space;

      do {
        nread = uv__recvmsg(uv__stream_fd(stream), &msg, 0);
      }
      while (nread < 0 && errno == EINTR);
    }

    if (nread < 0) {
      /* Error */
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        /* Wait for the next one. */
        if (stream->flags & UV_HANDLE_READING) {
          uv__io_start(stream->loop, &stream->io_watcher, POLLIN);
          uv__stream_osx_interrupt_select(stream);
        }
        stream->read_cb(stream, 0, &buf);
#if defined(__CYGWIN__) || defined(__MSYS__)
      } else if (errno == ECONNRESET && stream->type == UV_NAMED_PIPE) {
        uv__stream_eof(stream, &buf);
        return;
#elif defined(_AIX)
      } else if (errno == ECONNRESET && (stream->flags & UV_DISCONNECT)) {
        uv__stream_eof(stream, &buf);
        return;
#endif
      } else {
        /* Error. User should call uv_close(). */
        stream->read_cb(stream, UV__ERR(errno), &buf);
        if (stream->flags & UV_HANDLE_READING) {
          stream->flags &= ~UV_HANDLE_READING;
          uv__io_stop(stream->loop, &stream->io_watcher, POLLIN);
          if (!uv__io_active(&stream->io_watcher, POLLOUT))
            uv__handle_stop(stream);
          uv__stream_osx_interrupt_select(stream);
        }
      }
      return;
    } else if (nread == 0) {
      uv__stream_eof(stream, &buf);
      return;
    } else {
      /* Successful read */
      ssize_t buflen = buf.len;

      if (is_ipc) {
        err = uv__stream_recv_cmsg(stream, &msg);
        if (err != 0) {
          stream->read_cb(stream, err, &buf);
          return;
        }
      }

#if defined(__MVS__)
      if (is_ipc && msg.msg_controllen > 0) {
        uv_buf_t blankbuf;
        int nread;
        struct iovec *old;

        blankbuf.base = 0;
        blankbuf.len = 0;
        old = msg.msg_iov;
        msg.msg_iov = (struct iovec*) &blankbuf;
        nread = 0;
        do {
          nread = uv__recvmsg(uv__stream_fd(stream), &msg, 0);
          err = uv__stream_recv_cmsg(stream, &msg);
          if (err != 0) {
            stream->read_cb(stream, err, &buf);
            msg.msg_iov = old;
            return;
          }
        } while (nread == 0 && msg.msg_controllen > 0);
        msg.msg_iov = old;
      }
#endif
      stream->read_cb(stream, nread, &buf);

      /* Return if we didn't fill the buffer, there is no more data to read. */
      if (nread < buflen) {
        stream->flags |= UV_HANDLE_READ_PARTIAL;
        return;
      }
    }
  }
}
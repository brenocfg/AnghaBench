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
typedef  int /*<<< orphan*/  uv_file ;
struct TYPE_3__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int pread (int /*<<< orphan*/ ,scalar_t__,size_t,int) ; 

__attribute__((used)) static ssize_t uv__fs_preadv(uv_file fd,
                             uv_buf_t* bufs,
                             unsigned int nbufs,
                             off_t off) {
  uv_buf_t* buf;
  uv_buf_t* end;
  ssize_t result;
  ssize_t rc;
  size_t pos;

  assert(nbufs > 0);

  result = 0;
  pos = 0;
  buf = bufs + 0;
  end = bufs + nbufs;

  for (;;) {
    do
      rc = pread(fd, buf->base + pos, buf->len - pos, off + result);
    while (rc == -1 && errno == EINTR);

    if (rc == 0)
      break;

    if (rc == -1 && result == 0)
      return UV__ERR(errno);

    if (rc == -1)
      break;  /* We read some data so return that, ignore the error. */

    pos += rc;
    result += rc;

    if (pos < buf->len)
      continue;

    pos = 0;
    buf += 1;

    if (buf == end)
      break;
  }

  return result;
}
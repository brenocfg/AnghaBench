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
struct TYPE_4__ {unsigned int nbufs; scalar_t__ off; int /*<<< orphan*/ * bufs; int /*<<< orphan*/ * bufsml; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 unsigned int uv__fs_buf_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ uv__fs_write (TYPE_1__*) ; 
 unsigned int uv__getiovmax () ; 

__attribute__((used)) static ssize_t uv__fs_write_all(uv_fs_t* req) {
  unsigned int iovmax;
  unsigned int nbufs;
  uv_buf_t* bufs;
  ssize_t total;
  ssize_t result;

  iovmax = uv__getiovmax();
  nbufs = req->nbufs;
  bufs = req->bufs;
  total = 0;

  while (nbufs > 0) {
    req->nbufs = nbufs;
    if (req->nbufs > iovmax)
      req->nbufs = iovmax;

    do
      result = uv__fs_write(req);
    while (result < 0 && errno == EINTR);

    if (result <= 0) {
      if (total == 0)
        total = result;
      break;
    }

    if (req->off >= 0)
      req->off += result;

    req->nbufs = uv__fs_buf_offset(req->bufs, result);
    req->bufs += req->nbufs;
    nbufs -= req->nbufs;
    total += result;
  }

  if (bufs != req->bufsml)
    uv__free(bufs);

  req->bufs = NULL;
  req->nbufs = 0;

  return total;
}
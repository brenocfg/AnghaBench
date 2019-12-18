#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fd_out; int offset; TYPE_2__* bufsml; } ;
struct TYPE_11__ {TYPE_3__ info; } ;
struct TYPE_8__ {int fd; } ;
struct TYPE_12__ {TYPE_4__ fs; TYPE_1__ file; } ;
typedef  TYPE_5__ uv_fs_t ;
typedef  int int64_t ;
struct TYPE_9__ {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_5__*,int) ; 
 int _lseeki64 (int,int,int /*<<< orphan*/ ) ; 
 int _read (int,char*,size_t) ; 
 int _write (int,char*,int) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 scalar_t__ uv__malloc (size_t) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fs__sendfile(uv_fs_t* req) {
  int fd_in = req->file.fd, fd_out = req->fs.info.fd_out;
  size_t length = req->fs.info.bufsml[0].len;
  int64_t offset = req->fs.info.offset;
  const size_t max_buf_size = 65536;
  size_t buf_size = length < max_buf_size ? length : max_buf_size;
  int n, result = 0;
  int64_t result_offset = 0;
  char* buf = (char*) uv__malloc(buf_size);
  if (!buf) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  if (offset != -1) {
    result_offset = _lseeki64(fd_in, offset, SEEK_SET);
  }

  if (result_offset == -1) {
    result = -1;
  } else {
    while (length > 0) {
      n = _read(fd_in, buf, length < buf_size ? length : buf_size);
      if (n == 0) {
        break;
      } else if (n == -1) {
        result = -1;
        break;
      }

      length -= n;

      n = _write(fd_out, buf, n);
      if (n == -1) {
        result = -1;
        break;
      }

      result += n;
    }
  }

  uv__free(buf);

  SET_REQ_RESULT(req, result);
}
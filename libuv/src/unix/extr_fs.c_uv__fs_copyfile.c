#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ result; int /*<<< orphan*/  new_path; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  scalar_t__ uv_file ;
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; size_t st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FICLONE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int UV_ENOSYS ; 
 int UV_FS_COPYFILE_EXCL ; 
 int UV_FS_COPYFILE_FICLONE ; 
 int UV_FS_COPYFILE_FICLONE_FORCE ; 
 int UV__ERR (int) ; 
 int errno ; 
 int fchmod (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (scalar_t__,struct stat*) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int uv__close_nocheckstdio (scalar_t__) ; 
 scalar_t__ uv_fs_open (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_fs_sendfile (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_unlink (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t uv__fs_copyfile(uv_fs_t* req) {
  uv_fs_t fs_req;
  uv_file srcfd;
  uv_file dstfd;
  struct stat src_statsbuf;
  struct stat dst_statsbuf;
  int dst_flags;
  int result;
  int err;
  size_t bytes_to_send;
  int64_t in_offset;
  ssize_t bytes_written;

  dstfd = -1;
  err = 0;

  /* Open the source file. */
  srcfd = uv_fs_open(NULL, &fs_req, req->path, O_RDONLY, 0, NULL);
  uv_fs_req_cleanup(&fs_req);

  if (srcfd < 0)
    return srcfd;

  /* Get the source file's mode. */
  if (fstat(srcfd, &src_statsbuf)) {
    err = UV__ERR(errno);
    goto out;
  }

  dst_flags = O_WRONLY | O_CREAT | O_TRUNC;

  if (req->flags & UV_FS_COPYFILE_EXCL)
    dst_flags |= O_EXCL;

  /* Open the destination file. */
  dstfd = uv_fs_open(NULL,
                     &fs_req,
                     req->new_path,
                     dst_flags,
                     src_statsbuf.st_mode,
                     NULL);
  uv_fs_req_cleanup(&fs_req);

  if (dstfd < 0) {
    err = dstfd;
    goto out;
  }

  /* Get the destination file's mode. */
  if (fstat(dstfd, &dst_statsbuf)) {
    err = UV__ERR(errno);
    goto out;
  }

  /* Check if srcfd and dstfd refer to the same file */
  if (src_statsbuf.st_dev == dst_statsbuf.st_dev &&
      src_statsbuf.st_ino == dst_statsbuf.st_ino) {
    goto out;
  }

  if (fchmod(dstfd, src_statsbuf.st_mode) == -1) {
    err = UV__ERR(errno);
    goto out;
  }

#ifdef FICLONE
  if (req->flags & UV_FS_COPYFILE_FICLONE ||
      req->flags & UV_FS_COPYFILE_FICLONE_FORCE) {
    if (ioctl(dstfd, FICLONE, srcfd) == 0) {
      /* ioctl() with FICLONE succeeded. */
      goto out;
    }
    /* If an error occurred and force was set, return the error to the caller;
     * fall back to sendfile() when force was not set. */
    if (req->flags & UV_FS_COPYFILE_FICLONE_FORCE) {
      err = UV__ERR(errno);
      goto out;
    }
  }
#else
  if (req->flags & UV_FS_COPYFILE_FICLONE_FORCE) {
    err = UV_ENOSYS;
    goto out;
  }
#endif

  bytes_to_send = src_statsbuf.st_size;
  in_offset = 0;
  while (bytes_to_send != 0) {
    uv_fs_sendfile(NULL, &fs_req, dstfd, srcfd, in_offset, bytes_to_send, NULL);
    bytes_written = fs_req.result;
    uv_fs_req_cleanup(&fs_req);

    if (bytes_written < 0) {
      err = bytes_written;
      break;
    }

    bytes_to_send -= bytes_written;
    in_offset += bytes_written;
  }

out:
  if (err < 0)
    result = err;
  else
    result = 0;

  /* Close the source file. */
  err = uv__close_nocheckstdio(srcfd);

  /* Don't overwrite any existing errors. */
  if (err != 0 && result == 0)
    result = err;

  /* Close the destination file if it is open. */
  if (dstfd >= 0) {
    err = uv__close_nocheckstdio(dstfd);

    /* Don't overwrite any existing errors. */
    if (err != 0 && result == 0)
      result = err;

    /* Remove the destination file if something went wrong. */
    if (result != 0) {
      uv_fs_unlink(NULL, &fs_req, req->new_path, NULL);
      /* Ignore the unlink return value, as an error already happened. */
      uv_fs_req_cleanup(&fs_req);
    }
  }

  if (result == 0)
    return 0;

  errno = UV__ERR(result);
  return -1;
}
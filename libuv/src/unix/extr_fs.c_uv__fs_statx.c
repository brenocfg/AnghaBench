#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_15__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_19__ {scalar_t__ st_gen; scalar_t__ st_flags; TYPE_7__ st_birthtim; TYPE_5__ st_ctim; TYPE_3__ st_mtim; TYPE_1__ st_atim; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; scalar_t__ st_dev; } ;
typedef  TYPE_9__ uv_stat_t ;
struct TYPE_18__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_16__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_14__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct uv__statx {int stx_dev_major; TYPE_8__ stx_btime; TYPE_6__ stx_ctime; TYPE_4__ stx_mtime; TYPE_2__ stx_atime; int /*<<< orphan*/  stx_blocks; int /*<<< orphan*/  stx_blksize; int /*<<< orphan*/  stx_size; int /*<<< orphan*/  stx_ino; int /*<<< orphan*/  stx_rdev_major; int /*<<< orphan*/  stx_gid; int /*<<< orphan*/  stx_uid; int /*<<< orphan*/  stx_nlink; int /*<<< orphan*/  stx_mode; scalar_t__ stx_dev_minor; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  STATIC_ASSERT (int) ; 
 int UV_ENOSYS ; 
 scalar_t__ errno ; 
 int uv__statx (int,char const*,int,int,struct uv__statx*) ; 

__attribute__((used)) static int uv__fs_statx(int fd,
                        const char* path,
                        int is_fstat,
                        int is_lstat,
                        uv_stat_t* buf) {
  STATIC_ASSERT(UV_ENOSYS != -1);
#ifdef __linux__
  static int no_statx;
  struct uv__statx statxbuf;
  int dirfd;
  int flags;
  int mode;
  int rc;

  if (no_statx)
    return UV_ENOSYS;

  dirfd = AT_FDCWD;
  flags = 0; /* AT_STATX_SYNC_AS_STAT */
  mode = 0xFFF; /* STATX_BASIC_STATS + STATX_BTIME */

  if (is_fstat) {
    dirfd = fd;
    flags |= 0x1000; /* AT_EMPTY_PATH */
  }

  if (is_lstat)
    flags |= AT_SYMLINK_NOFOLLOW;

  rc = uv__statx(dirfd, path, flags, mode, &statxbuf);

  if (rc == -1) {
    /* EPERM happens when a seccomp filter rejects the system call.
     * Has been observed with libseccomp < 2.3.3 and docker < 18.04.
     */
    if (errno != EINVAL && errno != EPERM && errno != ENOSYS)
      return -1;

    no_statx = 1;
    return UV_ENOSYS;
  }

  buf->st_dev = 256 * statxbuf.stx_dev_major + statxbuf.stx_dev_minor;
  buf->st_mode = statxbuf.stx_mode;
  buf->st_nlink = statxbuf.stx_nlink;
  buf->st_uid = statxbuf.stx_uid;
  buf->st_gid = statxbuf.stx_gid;
  buf->st_rdev = statxbuf.stx_rdev_major;
  buf->st_ino = statxbuf.stx_ino;
  buf->st_size = statxbuf.stx_size;
  buf->st_blksize = statxbuf.stx_blksize;
  buf->st_blocks = statxbuf.stx_blocks;
  buf->st_atim.tv_sec = statxbuf.stx_atime.tv_sec;
  buf->st_atim.tv_nsec = statxbuf.stx_atime.tv_nsec;
  buf->st_mtim.tv_sec = statxbuf.stx_mtime.tv_sec;
  buf->st_mtim.tv_nsec = statxbuf.stx_mtime.tv_nsec;
  buf->st_ctim.tv_sec = statxbuf.stx_ctime.tv_sec;
  buf->st_ctim.tv_nsec = statxbuf.stx_ctime.tv_nsec;
  buf->st_birthtim.tv_sec = statxbuf.stx_btime.tv_sec;
  buf->st_birthtim.tv_nsec = statxbuf.stx_btime.tv_nsec;
  buf->st_flags = 0;
  buf->st_gen = 0;

  return 0;
#else
  return UV_ENOSYS;
#endif /* __linux__ */
}
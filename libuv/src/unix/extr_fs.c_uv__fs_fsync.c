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
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int F_FULLFSYNC ; 
 int fcntl (int /*<<< orphan*/ ,int) ; 
 int fsync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uv__fs_fsync(uv_fs_t* req) {
#if defined(__APPLE__)
  /* Apple's fdatasync and fsync explicitly do NOT flush the drive write cache
   * to the drive platters. This is in contrast to Linux's fdatasync and fsync
   * which do, according to recent man pages. F_FULLFSYNC is Apple's equivalent
   * for flushing buffered data to permanent storage. If F_FULLFSYNC is not
   * supported by the file system we fall back to F_BARRIERFSYNC or fsync().
   * This is the same approach taken by sqlite, except sqlite does not issue
   * an F_BARRIERFSYNC call.
   */
  int r;

  r = fcntl(req->file, F_FULLFSYNC);
  if (r != 0)
    r = fcntl(req->file, 85 /* F_BARRIERFSYNC */);  /* fsync + barrier */
  if (r != 0)
    r = fsync(req->file);
  return r;
#else
  return fsync(req->file);
#endif
}
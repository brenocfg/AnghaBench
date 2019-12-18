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
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdatasync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__fs_fsync (TYPE_1__*) ; 

__attribute__((used)) static ssize_t uv__fs_fdatasync(uv_fs_t* req) {
#if defined(__linux__) || defined(__sun) || defined(__NetBSD__)
  return fdatasync(req->file);
#elif defined(__APPLE__)
  /* See the comment in uv__fs_fsync. */
  return uv__fs_fsync(req);
#else
  return fsync(req->file);
#endif
}
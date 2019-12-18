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
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;

/* Variables and functions */
 int /*<<< orphan*/  COPYFILE ; 
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH2 ; 
 int /*<<< orphan*/  POST ; 
 int UV_EINVAL ; 
 int UV_FS_COPYFILE_EXCL ; 
 int UV_FS_COPYFILE_FICLONE ; 
 int UV_FS_COPYFILE_FICLONE_FORCE ; 

int uv_fs_copyfile(uv_loop_t* loop,
                   uv_fs_t* req,
                   const char* path,
                   const char* new_path,
                   int flags,
                   uv_fs_cb cb) {
  INIT(COPYFILE);

  if (flags & ~(UV_FS_COPYFILE_EXCL |
                UV_FS_COPYFILE_FICLONE |
                UV_FS_COPYFILE_FICLONE_FORCE)) {
    return UV_EINVAL;
  }

  PATH2;
  req->flags = flags;
  POST;
}
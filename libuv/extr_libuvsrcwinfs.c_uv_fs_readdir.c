#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_5__ {TYPE_2__* ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;
struct TYPE_6__ {scalar_t__ dir_handle; int /*<<< orphan*/ * dirents; } ;
typedef  TYPE_2__ uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  POST ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_FS_READDIR ; 

int uv_fs_readdir(uv_loop_t* loop,
                  uv_fs_t* req,
                  uv_dir_t* dir,
                  uv_fs_cb cb) {
  INIT(UV_FS_READDIR);

  if (dir == NULL ||
      dir->dirents == NULL ||
      dir->dir_handle == INVALID_HANDLE_VALUE) {
    return UV_EINVAL;
  }

  req->ptr = dir;
  POST;
}
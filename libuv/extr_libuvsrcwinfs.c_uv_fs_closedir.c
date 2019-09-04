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
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;
typedef  int /*<<< orphan*/  uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_FS_CLOSEDIR ; 

int uv_fs_closedir(uv_loop_t* loop,
                   uv_fs_t* req,
                   uv_dir_t* dir,
                   uv_fs_cb cb) {
  INIT(UV_FS_CLOSEDIR);
  if (dir == NULL)
    return UV_EINVAL;
  req->ptr = dir;
  POST;
}
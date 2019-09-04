#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_fs_t ;
typedef  int /*<<< orphan*/ * uv_fs_cb ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 
 int /*<<< orphan*/  UV_FS_LINK ; 
 int fs__capture_path (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 

int uv_fs_link(uv_loop_t* loop, uv_fs_t* req, const char* path,
    const char* new_path, uv_fs_cb cb) {
  int err;

  INIT(UV_FS_LINK);
  err = fs__capture_path(req, path, new_path, cb != NULL);
  if (err) {
    return uv_translate_sys_error(err);
  }

  POST;
}
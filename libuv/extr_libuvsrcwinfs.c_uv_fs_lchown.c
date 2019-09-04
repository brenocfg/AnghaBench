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
typedef  int /*<<< orphan*/  uv_uid_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_gid_t ;
typedef  int /*<<< orphan*/  uv_fs_t ;
typedef  int /*<<< orphan*/ * uv_fs_cb ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 
 int /*<<< orphan*/  UV_FS_LCHOWN ; 
 int fs__capture_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 

int uv_fs_lchown(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_uid_t uid,
    uv_gid_t gid, uv_fs_cb cb) {
  int err;

  INIT(UV_FS_LCHOWN);
  err = fs__capture_path(req, path, NULL, cb != NULL);
  if (err) {
    return uv_translate_sys_error(err);
  }
  POST;
}
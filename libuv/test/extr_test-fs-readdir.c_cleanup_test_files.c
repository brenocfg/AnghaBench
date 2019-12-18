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
typedef  int /*<<< orphan*/  uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv_fs_req_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_rmdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_unlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_test_files(void) {
  uv_fs_t req;

  uv_fs_unlink(NULL, &req, "test_dir/file1", NULL);
  uv_fs_req_cleanup(&req);
  uv_fs_unlink(NULL, &req, "test_dir/file2", NULL);
  uv_fs_req_cleanup(&req);
  uv_fs_rmdir(NULL, &req, "test_dir/test_subdir", NULL);
  uv_fs_req_cleanup(&req);
  uv_fs_rmdir(NULL, &req, "test_dir", NULL);
  uv_fs_req_cleanup(&req);
}
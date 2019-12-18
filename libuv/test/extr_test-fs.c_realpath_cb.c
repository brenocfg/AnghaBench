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
struct TYPE_4__ {scalar_t__ fs_type; scalar_t__ result; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  test_file_abs_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int PATHMAX ; 
 scalar_t__ UV_ENOSYS ; 
 scalar_t__ UV_FS_REALPATH ; 
 int /*<<< orphan*/  realpath_cb_count ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uv_cwd (char*,size_t*) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void realpath_cb(uv_fs_t* req) {
  char test_file_abs_buf[PATHMAX];
  size_t test_file_abs_size = sizeof(test_file_abs_buf);
  ASSERT(req->fs_type == UV_FS_REALPATH);
#ifdef _WIN32
  /*
   * Windows XP and Server 2003 don't support GetFinalPathNameByHandleW()
   */
  if (req->result == UV_ENOSYS) {
    realpath_cb_count++;
    uv_fs_req_cleanup(req);
    return;
  }
#endif
  ASSERT(req->result == 0);

  uv_cwd(test_file_abs_buf, &test_file_abs_size);
#ifdef _WIN32
  strcat(test_file_abs_buf, "\\test_file");
  ASSERT(stricmp(req->ptr, test_file_abs_buf) == 0);
#else
  strcat(test_file_abs_buf, "/test_file");
  ASSERT(strcmp(req->ptr, test_file_abs_buf) == 0);
#endif
  realpath_cb_count++;
  uv_fs_req_cleanup(req);
}
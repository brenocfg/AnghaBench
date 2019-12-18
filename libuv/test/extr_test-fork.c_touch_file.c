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
typedef  int uv_file ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int uv_fs_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int uv_fs_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (int /*<<< orphan*/ *) ; 
 int uv_fs_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void touch_file(const char* name) {
  int r;
  uv_file file;
  uv_fs_t req;
  uv_buf_t buf;

  r = uv_fs_open(NULL, &req, name, O_RDWR, 0, NULL);
  ASSERT(r >= 0);
  file = r;
  uv_fs_req_cleanup(&req);

  buf = uv_buf_init("foo", 4);
  r = uv_fs_write(NULL, &req, file, &buf, 1, -1, NULL);
  ASSERT(r >= 0);
  uv_fs_req_cleanup(&req);

  r = uv_fs_close(NULL, &req, file, NULL);
  ASSERT(r == 0);
  uv_fs_req_cleanup(&req);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 TYPE_1__ close_req ; 
 int /*<<< orphan*/  iov ; 
 int /*<<< orphan*/  loop ; 
 TYPE_1__ open_req1 ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  uv_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_fs_close (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int uv_fs_open (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int uv_fs_write (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ write_req ; 

__attribute__((used)) static void fs_file_write_null_buffer(int add_flags) {
  int r;

  /* Setup. */
  unlink("test_file");

  loop = uv_default_loop();

  r = uv_fs_open(NULL, &open_req1, "test_file",
      O_WRONLY | O_CREAT | add_flags, S_IWUSR | S_IRUSR, NULL);
  ASSERT(r >= 0);
  ASSERT(open_req1.result >= 0);
  uv_fs_req_cleanup(&open_req1);

  iov = uv_buf_init(NULL, 0);
  r = uv_fs_write(NULL, &write_req, open_req1.result, &iov, 1, -1, NULL);
  ASSERT(r == 0);
  ASSERT(write_req.result == 0);
  uv_fs_req_cleanup(&write_req);

  r = uv_fs_close(NULL, &close_req, open_req1.result, NULL);
  ASSERT(r == 0);
  ASSERT(close_req.result == 0);
  uv_fs_req_cleanup(&close_req);

  unlink("test_file");
}
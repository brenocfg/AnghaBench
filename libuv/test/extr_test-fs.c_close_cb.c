#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fs_type; scalar_t__ result; } ;
typedef  TYPE_1__ uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_CLOSE ; 
 int close_cb_count ; 
 TYPE_1__ close_req ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  unlink_cb ; 
 int /*<<< orphan*/  unlink_req ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int uv_fs_unlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_cb(uv_fs_t* req) {
  int r;
  ASSERT(req == &close_req);
  ASSERT(req->fs_type == UV_FS_CLOSE);
  ASSERT(req->result == 0);
  close_cb_count++;
  uv_fs_req_cleanup(req);
  if (close_cb_count == 3) {
    r = uv_fs_unlink(loop, &unlink_req, "test_file2", unlink_cb);
    ASSERT(r == 0);
  }
}
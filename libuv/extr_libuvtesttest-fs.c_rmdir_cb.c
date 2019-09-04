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
struct TYPE_5__ {scalar_t__ fs_type; scalar_t__ result; int path; } ;
typedef  TYPE_1__ uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_RMDIR ; 
 scalar_t__ memcmp (int,char*,int) ; 
 int /*<<< orphan*/  rmdir_cb_count ; 
 TYPE_1__ rmdir_req ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void rmdir_cb(uv_fs_t* req) {
  ASSERT(req == &rmdir_req);
  ASSERT(req->fs_type == UV_FS_RMDIR);
  ASSERT(req->result == 0);
  rmdir_cb_count++;
  ASSERT(req->path);
  ASSERT(memcmp(req->path, "test_dir\0", 9) == 0);
  uv_fs_req_cleanup(req);
}
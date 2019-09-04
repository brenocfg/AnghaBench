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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_READLINK ; 
 int /*<<< orphan*/  readlink_cb_count ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void readlink_cb(uv_fs_t* req) {
  ASSERT(req->fs_type == UV_FS_READLINK);
  ASSERT(req->result == 0);
  ASSERT(strcmp(req->ptr, "test_file_symlink2") == 0);
  readlink_cb_count++;
  uv_fs_req_cleanup(req);
}
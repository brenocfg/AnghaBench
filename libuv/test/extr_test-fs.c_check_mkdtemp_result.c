#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int st_mode; } ;
typedef  TYPE_1__ uv_stat_t ;
struct TYPE_8__ {scalar_t__ fs_type; scalar_t__ result; int path; } ;
typedef  TYPE_2__ uv_fs_t ;
struct TYPE_9__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int S_IFDIR ; 
 scalar_t__ UV_FS_MKDTEMP ; 
 int /*<<< orphan*/  check_permission (int,int) ; 
 scalar_t__ memcmp (int,char*,int) ; 
 TYPE_3__ stat_req ; 
 int strlen (int) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_3__*) ; 
 int uv_fs_stat (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_mkdtemp_result(uv_fs_t* req) {
  int r;

  ASSERT(req->fs_type == UV_FS_MKDTEMP);
  ASSERT(req->result == 0);
  ASSERT(req->path);
  ASSERT(strlen(req->path) == 15);
  ASSERT(memcmp(req->path, "test_dir_", 9) == 0);
  ASSERT(memcmp(req->path + 9, "XXXXXX", 6) != 0);
  check_permission(req->path, 0700);

  /* Check if req->path is actually a directory */
  r = uv_fs_stat(NULL, &stat_req, req->path, NULL);
  ASSERT(r == 0);
  ASSERT(((uv_stat_t*)stat_req.ptr)->st_mode & S_IFDIR);
  uv_fs_req_cleanup(&stat_req);
}
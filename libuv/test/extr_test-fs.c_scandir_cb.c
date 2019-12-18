#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ fs_type; int result; int ptr; int path; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ uv_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EOF ; 
 scalar_t__ UV_FS_SCANDIR ; 
 int /*<<< orphan*/  assert_is_file_type (TYPE_2__) ; 
 scalar_t__ memcmp (int,char*,int) ; 
 int /*<<< orphan*/  scandir_cb_count ; 
 TYPE_1__ scandir_req ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 scalar_t__ uv_fs_scandir_next (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void scandir_cb(uv_fs_t* req) {
  uv_dirent_t dent;
  ASSERT(req == &scandir_req);
  ASSERT(req->fs_type == UV_FS_SCANDIR);
  ASSERT(req->result == 2);
  ASSERT(req->ptr);

  while (UV_EOF != uv_fs_scandir_next(req, &dent)) {
    ASSERT(strcmp(dent.name, "file1") == 0 || strcmp(dent.name, "file2") == 0);
    assert_is_file_type(dent);
  }
  scandir_cb_count++;
  ASSERT(req->path);
  ASSERT(memcmp(req->path, "test_dir\0", 9) == 0);
  uv_fs_req_cleanup(req);
  ASSERT(!req->ptr);
}
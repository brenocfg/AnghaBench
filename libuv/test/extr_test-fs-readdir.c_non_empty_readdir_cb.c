#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ fs_type; scalar_t__ result; TYPE_2__* ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_14__ {int /*<<< orphan*/  nentries; TYPE_10__* dirents; } ;
typedef  TYPE_2__ uv_dir_t ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_10__*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_DIRENT_DIR ; 
 scalar_t__ UV_DIRENT_FILE ; 
 scalar_t__ UV_DIRENT_UNKNOWN ; 
 scalar_t__ UV_FS_READDIR ; 
 int /*<<< orphan*/  closedir_req ; 
 TYPE_10__* dirents ; 
 int /*<<< orphan*/  non_empty_closedir_cb ; 
 int non_empty_readdir_cb_count ; 
 TYPE_1__ readdir_req ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_fs_closedir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_fs_readdir (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,void (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void non_empty_readdir_cb(uv_fs_t* req) {
  uv_dir_t* dir;

  ASSERT(req == &readdir_req);
  ASSERT(req->fs_type == UV_FS_READDIR);
  dir = req->ptr;

  if (req->result == 0) {
    uv_fs_req_cleanup(req);
    ASSERT(non_empty_readdir_cb_count == 3);
    uv_fs_closedir(uv_default_loop(),
                   &closedir_req,
                   dir,
                   non_empty_closedir_cb);
  } else {
    ASSERT(req->result == 1);
    ASSERT(dir->dirents == dirents);
    ASSERT(strcmp(dirents[0].name, "file1") == 0 ||
           strcmp(dirents[0].name, "file2") == 0 ||
           strcmp(dirents[0].name, "test_subdir") == 0);
#ifdef HAVE_DIRENT_TYPES
    if (!strcmp(dirents[0].name, "test_subdir"))
      ASSERT(dirents[0].type == UV_DIRENT_DIR);
    else
      ASSERT(dirents[0].type == UV_DIRENT_FILE);
#else
    ASSERT(dirents[0].type == UV_DIRENT_UNKNOWN);
#endif /* HAVE_DIRENT_TYPES */

    ++non_empty_readdir_cb_count;
    uv_fs_req_cleanup(req);
    dir->dirents = dirents;
    dir->nentries = ARRAY_SIZE(dirents);
    uv_fs_readdir(uv_default_loop(),
                  &readdir_req,
                  dir,
                  non_empty_readdir_cb);
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ fs_type; scalar_t__ result; TYPE_2__* ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_8__ {int /*<<< orphan*/  nentries; int /*<<< orphan*/  dirents; } ;
typedef  TYPE_2__ uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_OPENDIR ; 
 int /*<<< orphan*/  dirents ; 
 int /*<<< orphan*/  empty_opendir_cb_count ; 
 int /*<<< orphan*/  empty_readdir_cb ; 
 TYPE_1__ opendir_req ; 
 int /*<<< orphan*/  readdir_req ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_fs_readdir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void empty_opendir_cb(uv_fs_t* req) {
  uv_dir_t* dir;
  int r;

  ASSERT(req == &opendir_req);
  ASSERT(req->fs_type == UV_FS_OPENDIR);
  ASSERT(req->result == 0);
  ASSERT(req->ptr != NULL);
  dir = req->ptr;
  dir->dirents = dirents;
  dir->nentries = ARRAY_SIZE(dirents);
  r = uv_fs_readdir(uv_default_loop(),
                    &readdir_req,
                    dir,
                    empty_readdir_cb);
  ASSERT(r == 0);
  uv_fs_req_cleanup(req);
  ++empty_opendir_cb_count;
}
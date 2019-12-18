#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fs_type; scalar_t__ result; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_ENOENT ; 
 scalar_t__ UV_FS_SCANDIR ; 
 int /*<<< orphan*/  scandir_cb_count ; 
 TYPE_1__ scandir_req ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 scalar_t__ uv_fs_scandir_next (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void non_existent_scandir_cb(uv_fs_t* req) {
  uv_dirent_t dent;

  ASSERT(req == &scandir_req);
  ASSERT(req->fs_type == UV_FS_SCANDIR);
  ASSERT(req->result == UV_ENOENT);
  ASSERT(req->ptr == NULL);
  ASSERT(UV_ENOENT == uv_fs_scandir_next(req, &dent));
  uv_fs_req_cleanup(req);
  scandir_cb_count++;
}
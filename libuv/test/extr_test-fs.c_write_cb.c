#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fs_type; scalar_t__ result; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_7__ {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_WRITE ; 
 int /*<<< orphan*/  fdatasync_cb ; 
 int /*<<< orphan*/  fdatasync_req ; 
 int /*<<< orphan*/  loop ; 
 TYPE_5__ open_req1 ; 
 int uv_fs_fdatasync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  write_cb_count ; 
 TYPE_1__ write_req ; 

__attribute__((used)) static void write_cb(uv_fs_t* req) {
  int r;
  ASSERT(req == &write_req);
  ASSERT(req->fs_type == UV_FS_WRITE);
  ASSERT(req->result >= 0);  /* FIXME(bnoordhuis) Check if requested size? */
  write_cb_count++;
  uv_fs_req_cleanup(req);
  r = uv_fs_fdatasync(loop, &fdatasync_req, open_req1.result, fdatasync_cb);
  ASSERT(r == 0);
}
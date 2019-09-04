#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ result; scalar_t__ fs_type; TYPE_2__* data; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_7__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ utime_check_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_FUTIME ; 
 int /*<<< orphan*/  check_utime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futime_cb_count ; 
 TYPE_1__ futime_req ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void futime_cb(uv_fs_t* req) {
  utime_check_t* c;

  ASSERT(req == &futime_req);
  ASSERT(req->result == 0);
  ASSERT(req->fs_type == UV_FS_FUTIME);

  c = req->data;
  check_utime(c->path, c->atime, c->mtime);

  uv_fs_req_cleanup(req);
  futime_cb_count++;
}
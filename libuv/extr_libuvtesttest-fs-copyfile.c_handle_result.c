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
struct TYPE_6__ {scalar_t__ st_size; scalar_t__ st_mode; } ;
struct TYPE_7__ {scalar_t__ fs_type; scalar_t__ result; TYPE_1__ statbuf; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_FS_COPYFILE ; 
 int /*<<< orphan*/  dst ; 
 int /*<<< orphan*/  result_check_count ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 
 int uv_fs_stat (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_result(uv_fs_t* req) {
  uv_fs_t stat_req;
  uint64_t size;
  uint64_t mode;
  int r;

  ASSERT(req->fs_type == UV_FS_COPYFILE);
  ASSERT(req->result == 0);

  /* Verify that the file size and mode are the same. */
  r = uv_fs_stat(NULL, &stat_req, req->path, NULL);
  ASSERT(r == 0);
  size = stat_req.statbuf.st_size;
  mode = stat_req.statbuf.st_mode;
  uv_fs_req_cleanup(&stat_req);
  r = uv_fs_stat(NULL, &stat_req, dst, NULL);
  ASSERT(r == 0);
  ASSERT(stat_req.statbuf.st_size == size);
  ASSERT(stat_req.statbuf.st_mode == mode);
  uv_fs_req_cleanup(&stat_req);
  uv_fs_req_cleanup(req);
  result_check_count++;
}
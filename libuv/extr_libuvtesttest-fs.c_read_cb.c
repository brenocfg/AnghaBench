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
 scalar_t__ UV_FS_READ ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  close_req ; 
 int /*<<< orphan*/  ftruncate_cb ; 
 int /*<<< orphan*/  ftruncate_req ; 
 int /*<<< orphan*/  loop ; 
 TYPE_5__ open_req1 ; 
 int read_cb_count ; 
 TYPE_1__ read_req ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* test_buf ; 
 int uv_fs_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_fs_ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void read_cb(uv_fs_t* req) {
  int r;
  ASSERT(req == &read_req);
  ASSERT(req->fs_type == UV_FS_READ);
  ASSERT(req->result >= 0);  /* FIXME(bnoordhuis) Check if requested size? */
  read_cb_count++;
  uv_fs_req_cleanup(req);
  if (read_cb_count == 1) {
    ASSERT(strcmp(buf, test_buf) == 0);
    r = uv_fs_ftruncate(loop, &ftruncate_req, open_req1.result, 7,
        ftruncate_cb);
  } else {
    ASSERT(strcmp(buf, "test-bu") == 0);
    r = uv_fs_close(loop, &close_req, open_req1.result, close_cb);
  }
  ASSERT(r == 0);
}
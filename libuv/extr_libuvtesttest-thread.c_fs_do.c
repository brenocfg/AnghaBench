#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fs_req {int /*<<< orphan*/  handle; int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fs_cb ; 
 int uv_fs_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_do(struct fs_req* req) {
  int r;

  r = uv_fs_stat(req->loop, &req->handle, ".", fs_cb);
  ASSERT(r == 0);
}
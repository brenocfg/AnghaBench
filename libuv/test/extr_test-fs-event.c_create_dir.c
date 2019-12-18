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
typedef  int /*<<< orphan*/  uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_EEXIST ; 
 int uv_fs_mkdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_dir(const char* name) {
  int r;
  uv_fs_t req;
  r = uv_fs_mkdir(NULL, &req, name, 0755, NULL);
  ASSERT(r == 0 || r == UV_EEXIST);
  uv_fs_req_cleanup(&req);
}
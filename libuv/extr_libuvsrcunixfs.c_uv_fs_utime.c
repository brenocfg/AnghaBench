#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_3__ {double atime; double mtime; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH ; 
 int /*<<< orphan*/  POST ; 
 int /*<<< orphan*/  UTIME ; 

int uv_fs_utime(uv_loop_t* loop,
                uv_fs_t* req,
                const char* path,
                double atime,
                double mtime,
                uv_fs_cb cb) {
  INIT(UTIME);
  PATH;
  req->atime = atime;
  req->mtime = mtime;
  POST;
}
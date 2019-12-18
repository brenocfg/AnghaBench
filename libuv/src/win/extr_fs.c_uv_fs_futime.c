#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_7__ {double atime; double mtime; } ;
struct TYPE_8__ {TYPE_2__ time; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {TYPE_3__ fs; TYPE_1__ file; } ;
typedef  TYPE_4__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;
typedef  int /*<<< orphan*/  uv_file ;

/* Variables and functions */
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 
 int /*<<< orphan*/  UV_FS_FUTIME ; 

int uv_fs_futime(uv_loop_t* loop, uv_fs_t* req, uv_file fd, double atime,
    double mtime, uv_fs_cb cb) {
  INIT(UV_FS_FUTIME);
  req->file.fd = fd;
  req->fs.time.atime = atime;
  req->fs.time.mtime = mtime;
  POST;
}
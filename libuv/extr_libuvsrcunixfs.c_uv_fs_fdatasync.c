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
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;
typedef  int /*<<< orphan*/  uv_file ;

/* Variables and functions */
 int /*<<< orphan*/  FDATASYNC ; 
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 

int uv_fs_fdatasync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
  INIT(FDATASYNC);
  req->file = file;
  POST;
}
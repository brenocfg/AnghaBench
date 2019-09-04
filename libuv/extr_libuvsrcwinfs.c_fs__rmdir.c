#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pathw; } ;
struct TYPE_6__ {TYPE_1__ file; } ;
typedef  TYPE_2__ uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_2__*,int) ; 
 int _wrmdir (int /*<<< orphan*/ ) ; 

void fs__rmdir(uv_fs_t* req) {
  int result = _wrmdir(req->file.pathw);
  SET_REQ_RESULT(req, result);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {TYPE_2__ info; } ;
struct TYPE_7__ {int /*<<< orphan*/  pathw; } ;
struct TYPE_10__ {TYPE_3__ fs; TYPE_1__ file; } ;
typedef  TYPE_4__ uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_4__*,int) ; 
 int _wchmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs__chmod(uv_fs_t* req) {
  int result = _wchmod(req->file.pathw, req->fs.info.mode);
  SET_REQ_RESULT(req, result);
}
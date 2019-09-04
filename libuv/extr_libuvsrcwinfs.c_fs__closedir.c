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
struct TYPE_6__ {TYPE_2__* ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_7__ {int /*<<< orphan*/  dir_handle; } ;
typedef  TYPE_2__ uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (TYPE_2__*) ; 

void fs__closedir(uv_fs_t* req) {
  uv_dir_t* dir;

  dir = req->ptr;
  FindClose(dir->dir_handle);
  uv__free(req->ptr);
  SET_REQ_RESULT(req, 0);
}
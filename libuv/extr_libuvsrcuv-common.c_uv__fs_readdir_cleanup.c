#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int result; TYPE_3__* ptr; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ uv_dirent_t ;
struct TYPE_7__ {TYPE_2__* dirents; } ;
typedef  TYPE_3__ uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__free (char*) ; 

void uv__fs_readdir_cleanup(uv_fs_t* req) {
  uv_dir_t* dir;
  uv_dirent_t* dirents;
  int i;

  if (req->ptr == NULL)
    return;

  dir = req->ptr;
  dirents = dir->dirents;
  req->ptr = NULL;

  if (dirents == NULL)
    return;

  for (i = 0; i < req->result; ++i) {
    uv__free((char*) dirents[i].name);
    dirents[i].name = NULL;
  }
}
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
struct TYPE_6__ {TYPE_2__* ptr; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dir; } ;
typedef  TYPE_2__ uv_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (TYPE_2__*) ; 
 TYPE_2__* uv__malloc (int) ; 

__attribute__((used)) static int uv__fs_opendir(uv_fs_t* req) {
  uv_dir_t* dir;

  dir = uv__malloc(sizeof(*dir));
  if (dir == NULL)
    goto error;

  dir->dir = opendir(req->path);
  if (dir->dir == NULL)
    goto error;

  req->ptr = dir;
  return 0;

error:
  uv__free(dir);
  req->ptr = NULL;
  return -1;
}
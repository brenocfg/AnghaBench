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
struct TYPE_3__ {int /*<<< orphan*/ ** ptr; scalar_t__ nbufs; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv__dirent_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int scandir (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__fs_scandir_filter ; 
 int /*<<< orphan*/  uv__fs_scandir_sort ; 

__attribute__((used)) static ssize_t uv__fs_scandir(uv_fs_t* req) {
  uv__dirent_t** dents;
  int n;

  dents = NULL;
  n = scandir(req->path, &dents, uv__fs_scandir_filter, uv__fs_scandir_sort);

  /* NOTE: We will use nbufs as an index field */
  req->nbufs = 0;

  if (n == 0) {
    /* OS X still needs to deallocate some memory.
     * Memory was allocated using the system allocator, so use free() here.
     */
    free(dents);
    dents = NULL;
  } else if (n == -1) {
    return n;
  }

  req->ptr = dents;

  return n;
}
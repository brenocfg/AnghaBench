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
struct TYPE_3__ {unsigned int nbufs; } ;
typedef  TYPE_1__ uv_fs_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int* uv__get_nbufs(uv_fs_t* req) {
#ifdef _WIN32
  return &req->fs.info.nbufs;
#else
  return &req->nbufs;
#endif
}
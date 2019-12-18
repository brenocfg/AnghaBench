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
struct TYPE_3__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int,long long) ; 
 int pread (int /*<<< orphan*/ ,void*,int,long long) ; 

int vk_pread (file_t *F, void *a, int sz, long long off) {
  if (sz != pread (F->fd, a, sz, off)) {
    kprintf ("pread (%s, %d, %lld) failed. %m\n", F->filename, sz, off);
    return -1;
  }
  return 0;
}
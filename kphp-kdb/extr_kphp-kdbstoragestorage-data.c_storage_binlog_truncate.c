#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int binlogs; TYPE_1__** B; } ;
typedef  TYPE_2__ volume_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {scalar_t__ fd_wronly; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftruncate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void storage_binlog_truncate (volume_t *V, off_t off) {
  int k;
  for (k = 0; k < V->binlogs; k++) {
    if (V->B[k]->fd_wronly >= 0) {
      ftruncate (V->B[k]->fd_wronly, off);
    }
  }
}
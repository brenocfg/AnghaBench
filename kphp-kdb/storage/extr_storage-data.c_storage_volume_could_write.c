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
struct TYPE_7__ {int binlogs; TYPE_2__** B; } ;
typedef  TYPE_3__ volume_t ;
struct TYPE_5__ {scalar_t__ fails; } ;
struct TYPE_6__ {scalar_t__ fd_wronly; TYPE_1__ st_fsync; } ;

/* Variables and functions */
 int STORAGE_ERR_NO_WRONLY_BINLOGS ; 

__attribute__((used)) static int storage_volume_could_write (volume_t *V) {
  int k;
  for (k = 0; k < V->binlogs; k++) {
    if (V->B[k]->fd_wronly >= 0 && V->B[k]->st_fsync.fails == 0) {
      return 0;
    }
  }
  return STORAGE_ERR_NO_WRONLY_BINLOGS;
}
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
struct TYPE_4__ {scalar_t__ fd_rdonly; int /*<<< orphan*/  abs_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void storage_open_binlogs (volume_t *V) {
  int k;
  for (k = 0; k < V->binlogs; k++) {
    if (V->B[k]->fd_rdonly < 0) {
      V->B[k]->fd_rdonly = open (V->B[k]->abs_filename, O_RDONLY);
      if (V->B[k]->fd_rdonly < 0) {
        kprintf ("Couldn't open %s for reading. %m\n", V->B[k]->abs_filename);
        exit (1);
      }
    }
  }
}
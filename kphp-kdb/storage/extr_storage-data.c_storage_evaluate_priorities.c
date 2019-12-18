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
struct TYPE_5__ {int binlogs; int volume_id; TYPE_1__** B; } ;
typedef  TYPE_2__ volume_t ;
struct TYPE_4__ {scalar_t__ dir_id; int priority; } ;

/* Variables and functions */
 int MAX_VOLUME_BINLOGS ; 

void storage_evaluate_priorities (volume_t *V) {
  int i, j, k, id[MAX_VOLUME_BINLOGS];
  for (i = 0; i < V->binlogs; i++) {
    id[i] = i;
  }
  for (i = 0; i < V->binlogs; i++) {
    for (j = i + 1; j < V->binlogs; j++) {
      if (V->B[id[i]]->dir_id > V->B[id[j]]->dir_id) {
        k = id[i]; id[i] = id[j]; id[j] = k;
      }
    }
  }
  for (k = 0; k < V->binlogs; k++) {
    V->B[id[k]]->priority = (V->volume_id + k) % (V->binlogs);
  }
}
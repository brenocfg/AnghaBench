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
struct TYPE_3__ {long long node_id; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 TYPE_1__** Clusters ; 
 int max_cluster ; 

int choose_cluster (long long local_id) {
  int i;
  for (i = 0; i < max_cluster; i++) if (Clusters[i] && Clusters[i]->node_id == local_id) {
    CC = Clusters[i];
    return i;
  }
  return -1;
}
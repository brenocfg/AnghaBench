#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mc_cluster {int /*<<< orphan*/  a_timeouts; int /*<<< orphan*/  a_sbytes; int /*<<< orphan*/  a_rbytes; int /*<<< orphan*/  a_req; } ;
struct TYPE_2__ {int clusters_num; struct mc_cluster* Clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMORT_FACTOR ; 
 TYPE_1__* CurConf ; 

void adjust_cluster_stats (void) {
  int i;
  struct mc_cluster *C = CurConf->Clusters;
  for (i = 0; i < CurConf->clusters_num; i++, C++) {
    C->a_req *= AMORT_FACTOR;
    C->a_rbytes *= AMORT_FACTOR;
    C->a_sbytes *= AMORT_FACTOR;
    C->a_timeouts *= AMORT_FACTOR;
  }
}
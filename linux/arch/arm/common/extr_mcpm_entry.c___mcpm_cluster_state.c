#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* clusters; } ;
struct TYPE_3__ {int cluster; } ;

/* Variables and functions */
 TYPE_2__ mcpm_sync ; 
 int /*<<< orphan*/  sync_cache_r (int*) ; 

__attribute__((used)) static int __mcpm_cluster_state(unsigned int cluster)
{
	sync_cache_r(&mcpm_sync.clusters[cluster].cluster);
	return mcpm_sync.clusters[cluster].cluster;
}
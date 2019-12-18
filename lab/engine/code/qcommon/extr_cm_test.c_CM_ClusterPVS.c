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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int numClusters; int clusterBytes; int /*<<< orphan*/ * visibility; int /*<<< orphan*/  vised; } ;

/* Variables and functions */
 TYPE_1__ cm ; 

byte	*CM_ClusterPVS (int cluster) {
	if (cluster < 0 || cluster >= cm.numClusters || !cm.vised ) {
		return cm.visibility;
	}

	return cm.visibility + cluster * cm.clusterBytes;
}
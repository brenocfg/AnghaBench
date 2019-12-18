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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {TYPE_1__* world; } ;
struct TYPE_3__ {int numClusters; int clusterBytes; int /*<<< orphan*/  const* vis; int /*<<< orphan*/  const* novis; } ;

/* Variables and functions */
 TYPE_2__ tr ; 

__attribute__((used)) static const byte *R_ClusterPVS (int cluster) {
	if (!tr.world->vis || cluster < 0 || cluster >= tr.world->numClusters ) {
		return tr.world->novis;
	}

	return tr.world->vis + cluster * tr.world->clusterBytes;
}
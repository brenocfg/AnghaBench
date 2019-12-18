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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {int numareas; } ;

/* Variables and functions */
 int AAS_AreaCluster (int) ; 
 int /*<<< orphan*/  AAS_FloodAreas_r (int,int,int*) ; 
 int AAS_PointAreaNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeMemory (int*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_1__ aasworld ; 

void AAS_FloodAreas(vec3_t origin)
{
	int areanum, cluster, *done;

	done = (int *) GetClearedMemory(aasworld.numareas * sizeof(int));
	areanum = AAS_PointAreaNum(origin);
	cluster = AAS_AreaCluster(areanum);
	AAS_FloodAreas_r(areanum, cluster, done);
	FreeMemory(done);
}
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
struct TYPE_2__ {int cluster; } ;

/* Variables and functions */
 int PointInLeafNum (int /*<<< orphan*/ ) ; 
 TYPE_1__* bspLeafs ; 

int ClusterForPoint( vec3_t point ){
	int leafNum;


	/* get leafNum for point */
	leafNum = PointInLeafNum( point );
	if ( leafNum < 0 ) {
		return -1;
	}

	/* return the cluster */
	return bspLeafs[ leafNum ].cluster;
}
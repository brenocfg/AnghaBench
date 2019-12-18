#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ dplane_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_PLANES ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dplanes ; 
 TYPE_1__* mapplanes ; 
 int nummapplanes ; 
 size_t numplanes ; 

void EmitPlanes (void)
{
	int			i;
	dplane_t	*dp;
	plane_t		*mp;
	//ME: this causes a crash??
//	int		planetranslate[MAX_MAP_PLANES];

	mp = mapplanes;
	for (i=0 ; i<nummapplanes ; i++, mp++)
	{
		dp = &dplanes[numplanes];
//		planetranslate[i] = numplanes;
		VectorCopy ( mp->normal, dp->normal);
		dp->dist = mp->dist;
		dp->type = mp->type;
		numplanes++;
		if (numplanes >= MAX_MAP_PLANES)
			Error("MAX_MAP_PLANES");
	}
}
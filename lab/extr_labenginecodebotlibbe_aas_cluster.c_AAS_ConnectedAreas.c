#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  connectedareas ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ConnectedAreas_r (int*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (int*,int /*<<< orphan*/ ,int) ; 
 int MAX_PORTALAREAS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean AAS_ConnectedAreas(int *areanums, int numareas)
{
	int connectedareas[MAX_PORTALAREAS], i;

	Com_Memset(connectedareas, 0, sizeof(connectedareas));
	if (numareas < 1) return qfalse;
	if (numareas == 1) return qtrue;
	AAS_ConnectedAreas_r(areanums, numareas, connectedareas, 0);
	for (i = 0; i < numareas; i++)
	{
		if (!connectedareas[i]) return qfalse;
	} //end for
	return qtrue;
}
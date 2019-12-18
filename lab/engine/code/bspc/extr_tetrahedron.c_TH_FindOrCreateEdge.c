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

/* Variables and functions */
 int TH_CreateEdge (int,int) ; 
 int TH_FindEdge (int,int) ; 

int TH_FindOrCreateEdge(int v1, int v2)
{
	int edgenum;

	edgenum = TH_FindEdge(v1, v2);
	if (!edgenum) edgenum = TH_CreateEdge(v1, v2);
	return edgenum;
}
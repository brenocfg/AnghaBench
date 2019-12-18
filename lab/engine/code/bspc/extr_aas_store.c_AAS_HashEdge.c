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
 int EDGE_HASH_SIZE ; 

unsigned AAS_HashEdge(int v1, int v2)
{
	int vnum1, vnum2;
	//
	if (v1 < v2)
	{
		vnum1 = v1;
		vnum2 = v2;
	} //end if
	else
	{
		vnum1 = v2;
		vnum2 = v1;
	} //end else
	return (vnum1 + vnum2) & (EDGE_HASH_SIZE-1);
}
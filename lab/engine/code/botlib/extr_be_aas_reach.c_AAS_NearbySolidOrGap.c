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
typedef  int* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AreaGrounded (int) ; 
 int /*<<< orphan*/  AAS_AreaSwim (int) ; 
 int AAS_PointAreaNum (int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 int qfalse ; 
 int qtrue ; 

int AAS_NearbySolidOrGap(vec3_t start, vec3_t end)
{
	vec3_t dir, testpoint;
	int areanum;

	VectorSubtract(end, start, dir);
	dir[2] = 0;
	VectorNormalize(dir);
	VectorMA(end, 48, dir, testpoint);

	areanum = AAS_PointAreaNum(testpoint);
	if (!areanum)
	{
		testpoint[2] += 16;
		areanum = AAS_PointAreaNum(testpoint);
		if (!areanum) return qtrue;
	} //end if
	VectorMA(end, 64, dir, testpoint);
	areanum = AAS_PointAreaNum(testpoint);
	if (areanum)
	{
		if (!AAS_AreaSwim(areanum) && !AAS_AreaGrounded(areanum)) return qtrue;
	} //end if
	return qfalse;
}
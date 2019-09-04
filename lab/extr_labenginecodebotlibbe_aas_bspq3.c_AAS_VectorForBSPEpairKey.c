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
typedef  double* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 
 int MAX_EPAIRKEY ; 
 int /*<<< orphan*/  VectorClear (double*) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  sscanf (char*,char*,double*,double*,double*) ; 

int AAS_VectorForBSPEpairKey(int ent, char *key, vec3_t v)
{
	char buf[MAX_EPAIRKEY];
	double v1, v2, v3;

	VectorClear(v);
	if (!AAS_ValueForBSPEpairKey(ent, key, buf, MAX_EPAIRKEY)) return qfalse;
	//scanf into doubles, then assign, so it is vec_t size independent
	v1 = v2 = v3 = 0;
	sscanf(buf, "%lf %lf %lf", &v1, &v2, &v3);
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	return qtrue;
}
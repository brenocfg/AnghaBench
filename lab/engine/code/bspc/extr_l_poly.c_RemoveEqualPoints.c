#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_POINTS_ON_WINDING ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void RemoveEqualPoints(winding_t *w, float epsilon)
{
	int i, nump;
	vec3_t v;
	vec3_t p[MAX_POINTS_ON_WINDING];

	VectorCopy(w->p[0], p[0]);
	nump = 1;
	for (i = 1; i < w->numpoints; i++)
	{
		VectorSubtract(w->p[i], p[nump-1], v);
		if (VectorLength(v) > epsilon)
		{
			if (nump >= MAX_POINTS_ON_WINDING)
				Error("RemoveColinearPoints: MAX_POINTS_ON_WINDING");
			VectorCopy (w->p[i], p[nump]);
			nump++;
		} //end if
	} //end for

	if (nump == w->numpoints)
		return;

	w->numpoints = nump;
	memcpy(w->p, p, nump * sizeof(p[0]));
}
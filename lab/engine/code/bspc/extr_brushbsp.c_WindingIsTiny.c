#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int qboolean ;

/* Variables and functions */
 scalar_t__ EDGE_LENGTH ; 
 scalar_t__ VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WindingArea (TYPE_1__*) ; 

qboolean WindingIsTiny (winding_t *w)
{
#if 0
	if (WindingArea (w) < 1)
		return true;
	return false;
#else
	int		i, j;
	vec_t	len;
	vec3_t	delta;
	int		edges;

	edges = 0;
	for (i=0 ; i<w->numpoints ; i++)
	{
		j = i == w->numpoints - 1 ? 0 : i+1;
		VectorSubtract (w->p[j], w->p[i], delta);
		len = VectorLength (delta);
		if (len > EDGE_LENGTH)
		{
			if (++edges == 3)
				return false;
		}
	}
	return true;
#endif
}
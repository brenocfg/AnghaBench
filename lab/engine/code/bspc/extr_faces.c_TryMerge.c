#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {scalar_t__ texinfo; scalar_t__ planenum; scalar_t__ contents; struct TYPE_7__* merged; int /*<<< orphan*/ * w; } ;
typedef  TYPE_1__ face_t ;

/* Variables and functions */
 TYPE_1__* NewFaceFromFace (TYPE_1__*) ; 
 int /*<<< orphan*/ * TryMergeWinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_merge ; 

face_t *TryMerge (face_t *f1, face_t *f2, vec3_t planenormal)
{
	face_t		*newf;
	winding_t	*nw;

	if (!f1->w || !f2->w)
		return NULL;
	if (f1->texinfo != f2->texinfo)
		return NULL;
	if (f1->planenum != f2->planenum)	// on front and back sides
		return NULL;
	if (f1->contents != f2->contents)
		return NULL;
		

	nw = TryMergeWinding (f1->w, f2->w, planenormal);
	if (!nw)
		return NULL;

	c_merge++;
	newf = NewFaceFromFace (f1);
	newf->w = nw;

	f1->merged = newf;
	f2->merged = newf;

	return newf;
}
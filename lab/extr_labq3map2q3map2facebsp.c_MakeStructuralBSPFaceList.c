#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {int compileFlags; int planenum; int /*<<< orphan*/ * winding; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_8__ {int planenum; int compileFlags; struct TYPE_8__* next; scalar_t__ priority; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ face_t ;
struct TYPE_9__ {int numsides; TYPE_1__* sides; scalar_t__ detail; struct TYPE_9__* next; } ;
typedef  TYPE_3__ brush_t ;

/* Variables and functions */
 scalar_t__ ANTIPORTAL_PRIORITY ; 
 scalar_t__ AREAPORTAL_PRIORITY ; 
 TYPE_2__* AllocBspFace () ; 
 int C_ANTIPORTAL ; 
 int C_AREAPORTAL ; 
 int C_HINT ; 
 int C_SKIP ; 
 int /*<<< orphan*/  CopyWinding (int /*<<< orphan*/ *) ; 
 scalar_t__ HINT_PRIORITY ; 

face_t *MakeStructuralBSPFaceList( brush_t *list ){
	brush_t     *b;
	int i;
	side_t      *s;
	winding_t   *w;
	face_t      *f, *flist;


	flist = NULL;
	for ( b = list; b != NULL; b = b->next )
	{
		if ( b->detail ) {
			continue;
		}

		for ( i = 0; i < b->numsides; i++ )
		{
			/* get side and winding */
			s = &b->sides[ i ];
			w = s->winding;
			if ( w == NULL ) {
				continue;
			}

			/* ydnar: skip certain faces */
			if ( s->compileFlags & C_SKIP ) {
				continue;
			}

			/* allocate a face */
			f = AllocBspFace();
			f->w = CopyWinding( w );
			f->planenum = s->planenum & ~1;
			f->compileFlags = s->compileFlags;  /* ydnar */

			/* ydnar: set priority */
			f->priority = 0;
			if ( f->compileFlags & C_HINT ) {
				f->priority += HINT_PRIORITY;
			}
			if ( f->compileFlags & C_ANTIPORTAL ) {
				f->priority += ANTIPORTAL_PRIORITY;
			}
			if ( f->compileFlags & C_AREAPORTAL ) {
				f->priority += AREAPORTAL_PRIORITY;
			}

			/* get next face */
			f->next = flist;
			flist = f;
		}
	}

	return flist;
}
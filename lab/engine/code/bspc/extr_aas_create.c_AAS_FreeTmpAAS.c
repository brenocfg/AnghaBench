#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* settings; struct TYPE_6__* l_next; scalar_t__ winding; } ;
typedef  TYPE_1__ tmp_nodebuf_t ;
typedef  TYPE_1__ tmp_face_t ;
typedef  TYPE_1__ tmp_area_t ;
struct TYPE_7__ {TYPE_1__* nodebuffer; TYPE_1__* areas; TYPE_1__* faces; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 TYPE_4__ tmpaasworld ; 

void AAS_FreeTmpAAS(void)
{
	tmp_face_t *f, *nextf;
	tmp_area_t *a, *nexta;
	tmp_nodebuf_t *nb, *nextnb;

	//free all the faces
	for (f = tmpaasworld.faces; f; f = nextf)
	{
		nextf = f->l_next;
		if (f->winding) FreeWinding(f->winding);
		FreeMemory(f);
	} //end if
	//free all tmp areas
	for (a = tmpaasworld.areas; a; a = nexta)
	{
		nexta = a->l_next;
		if (a->settings) FreeMemory(a->settings);
		FreeMemory(a);
	} //end for
	//free all the tmp nodes
	for (nb = tmpaasworld.nodebuffer; nb; nb = nextnb)
	{
		nextnb = nb->next;
		FreeMemory(nb);
	} //end for
}
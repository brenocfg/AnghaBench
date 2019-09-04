#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ texinfo; int flags; int /*<<< orphan*/  winding; } ;
typedef  TYPE_1__ side_t ;
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_5__ {int numsides; TYPE_1__* sides; struct TYPE_5__* next; } ;
typedef  TYPE_2__ bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  GLS_BeginScene () ; 
 int /*<<< orphan*/  GLS_EndScene () ; 
 int /*<<< orphan*/  GLS_Winding (int /*<<< orphan*/ ,int) ; 
 int SFL_VISIBLE ; 
 scalar_t__ TEXINFO_NODE ; 

void DrawBrushList (bspbrush_t *brush, node_t *node)
{
	int		i;
	side_t	*s;

	GLS_BeginScene ();
	for ( ; brush ; brush=brush->next)
	{
		for (i=0 ; i<brush->numsides ; i++)
		{
			s = &brush->sides[i];
			if (!s->winding)
				continue;
			if (s->texinfo == TEXINFO_NODE)
				GLS_Winding (s->winding, 1);
			else if (!(s->flags & SFL_VISIBLE))
				GLS_Winding (s->winding, 2);
			else
				GLS_Winding (s->winding, 0);
		}
	}
	GLS_EndScene ();
}
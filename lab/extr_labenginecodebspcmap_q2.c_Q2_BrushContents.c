#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int contents; size_t texinfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_6__ {int numsides; int /*<<< orphan*/  brushnum; int /*<<< orphan*/  entitynum; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int CONTENTS_Q2TRANSLUCENT ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WINDOW ; 
 int /*<<< orphan*/  Log_Print (char*,int /*<<< orphan*/ ,...) ; 
 int SURF_TRANS33 ; 
 int SURF_TRANS66 ; 
 TYPE_3__* texinfo ; 

int	Q2_BrushContents (mapbrush_t *b)
{
	int			contents;
	side_t		*s;
	int			i;
	int			trans;

	s = &b->original_sides[0];
	contents = s->contents;
	trans = texinfo[s->texinfo].flags;
	for (i = 1; i < b->numsides; i++, s++)
	{
		s = &b->original_sides[i];
		trans |= texinfo[s->texinfo].flags;
		if (s->contents != contents)
		{
			Log_Print("Entity %i, Brush %i: mixed face contents\n"
				, b->entitynum, b->brushnum);
			Log_Print("texture name = %s\n", texinfo[s->texinfo].texture);
			break;
		}
	}

	// if any side is translucent, mark the contents
	// and change solid to window
	if ( trans & (SURF_TRANS33|SURF_TRANS66) )
	{
		contents |= CONTENTS_Q2TRANSLUCENT;
		if (contents & CONTENTS_SOLID)
		{
			contents &= ~CONTENTS_SOLID;
			contents |= CONTENTS_WINDOW;
		}
	}

	return contents;
}
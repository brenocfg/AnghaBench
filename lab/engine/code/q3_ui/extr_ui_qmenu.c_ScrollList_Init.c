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
struct TYPE_4__ {int left; int x; int right; int flags; scalar_t__ y; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_5__ {int columns; int separation; int width; int height; TYPE_1__ generic; scalar_t__ top; scalar_t__ curvalue; scalar_t__ oldvalue; } ;
typedef  TYPE_2__ menulist_s ;

/* Variables and functions */
 int QMF_CENTER_JUSTIFY ; 
 int SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 

__attribute__((used)) static void ScrollList_Init( menulist_s *l )
{
	int		w;

	l->oldvalue = 0;
	l->curvalue = 0;
	l->top      = 0;

	if( !l->columns ) {
		l->columns = 1;
		l->separation = 0;
	}
	else if( !l->separation ) {
		l->separation = 3;
	}

	w = ( (l->width + l->separation) * l->columns - l->separation) * SMALLCHAR_WIDTH;

	l->generic.left   =	l->generic.x;
	l->generic.top    = l->generic.y;	
	l->generic.right  =	l->generic.x + w;
	l->generic.bottom =	l->generic.y + l->height * SMALLCHAR_HEIGHT;

	if( l->generic.flags & QMF_CENTER_JUSTIFY ) {
		l->generic.left -= w / 2;
		l->generic.right -= w / 2;
	}
}
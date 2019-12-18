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
struct TYPE_5__ {int nLines; int /*<<< orphan*/  layout; TYPE_1__* lineMetrics; } ;
typedef  TYPE_2__ uiDrawTextLayout ;
struct TYPE_4__ {double Y; double Height; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairoToPango (double) ; 
 int pango_layout_get_line_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_xy_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

void uiDrawTextLayoutHitTest(uiDrawTextLayout *tl, double x, double y, size_t *pos, int *line)
{
	int p, trailing;
	int i;

	// this is layout-global, so it takes line origins into account
	pango_layout_xy_to_index(tl->layout,
		cairoToPango(x), cairoToPango(y),
		&p, &trailing);
	// on a trailing hit, align to the nearest cluster
	// fortunately Pango provides that info directly
	if (trailing != 0)
		p += trailing;
	*pos = p;

	for (i = 0; i < tl->nLines; i++) {
		double ltop, lbottom;

		ltop = tl->lineMetrics[i].Y;
		lbottom = ltop + tl->lineMetrics[i].Height;
		// y will already >= ltop at this point since the past lbottom should == ltop
		if (y < lbottom)
			break;
	}
	if (i == pango_layout_get_line_count(tl->layout))
		i--;
	*line = i;
}
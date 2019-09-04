#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ ParagraphSpacing; scalar_t__ LineSpacing; scalar_t__ LineHeightSpace; scalar_t__ ParagraphSpacingBefore; scalar_t__ Leading; void* Descent; void* Ascent; void* BaselineY; void* Height; void* Width; void* Y; void* X; } ;
typedef  TYPE_1__ uiDrawTextLayoutLineMetrics ;
struct TYPE_13__ {int nLines; int /*<<< orphan*/  layout; TYPE_1__* lineMetrics; } ;
typedef  TYPE_2__ uiDrawTextLayout ;
struct TYPE_15__ {int /*<<< orphan*/  start_index; } ;
struct TYPE_14__ {int x; int width; int height; } ;
typedef  TYPE_3__ PangoRectangle ;
typedef  TYPE_4__ PangoLayoutLine ;
typedef  int /*<<< orphan*/  PangoLayoutIter ;

/* Variables and functions */
 int PANGO_ASCENT (TYPE_3__) ; 
 int PANGO_DESCENT (TYPE_3__) ; 
 void* pangoToCairo (int) ; 
 int /*<<< orphan*/ * pango_layout_get_iter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_index_to_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pango_layout_iter_free (int /*<<< orphan*/ *) ; 
 int pango_layout_iter_get_baseline (int /*<<< orphan*/ *) ; 
 TYPE_4__* pango_layout_iter_get_line_readonly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_iter_next_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_line_get_extents (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ uiAlloc (int,char*) ; 

__attribute__((used)) static void computeLineMetrics(uiDrawTextLayout *tl)
{
	PangoLayoutIter *iter;
	PangoLayoutLine *pll;
	PangoRectangle lineStartPos, lineExtents;
	int i, n;
	uiDrawTextLayoutLineMetrics *m;

	n = tl->nLines;		// TODO remove this variable
	tl->lineMetrics = (uiDrawTextLayoutLineMetrics *) uiAlloc(n * sizeof (uiDrawTextLayoutLineMetrics), "uiDrawTextLayoutLineMetrics[] (text layout)");
	iter = pango_layout_get_iter(tl->layout);

	m = tl->lineMetrics;
	for (i = 0; i < n; i++) {
		int baselineY;

		// TODO we use this instead of _get_yrange() because of the block of text in that function's description about how line spacing is distributed in Pango; we have to worry about this when we start adding line spacing...
		baselineY = pango_layout_iter_get_baseline(iter);
		pll = pango_layout_iter_get_line_readonly(iter);
		pango_layout_index_to_pos(tl->layout, pll->start_index, &lineStartPos);
		pango_layout_line_get_extents(pll, NULL, &lineExtents);
		// TODO unref pll?

		// TODO is this correct for RTL glyphs?
		m->X = pangoToCairo(lineStartPos.x);
		// TODO fix the whole combined not being updated shenanigans in the static build (here because ugh)
		m->Y = pangoToCairo(baselineY - PANGO_ASCENT(lineExtents));
		// TODO this does not include the last space if any
		m->Width = pangoToCairo(lineExtents.width);
		m->Height = pangoToCairo(lineExtents.height);

		m->BaselineY = pangoToCairo(baselineY);
		m->Ascent = pangoToCairo(PANGO_ASCENT(lineExtents));
		m->Descent = pangoToCairo(PANGO_DESCENT(lineExtents));
		m->Leading = 0;		// TODO

		m->ParagraphSpacingBefore = 0;		// TODO
		m->LineHeightSpace = 0;				// TODO
		m->LineSpacing = 0;				// TODO
		m->ParagraphSpacing = 0;			// TODO

		// don't worry about the return value; we're not using this after the last line
		pango_layout_iter_next_line(iter);
		m++;
	}

	pango_layout_iter_free(iter);
}
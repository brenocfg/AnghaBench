#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* UnderlineThickness; void* UnderlinePos; scalar_t__ Leading; void* Descent; void* Ascent; } ;
typedef  TYPE_1__ uiDrawTextFontMetrics ;
struct TYPE_6__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ uiDrawTextFont ;
typedef  int /*<<< orphan*/  PangoFontMetrics ;

/* Variables and functions */
 void* pangoToCairo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pango_font_get_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_get_ascent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_get_descent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_get_underline_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_get_underline_thickness (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_unref (int /*<<< orphan*/ *) ; 

void uiDrawTextFontGetMetrics(uiDrawTextFont *font, uiDrawTextFontMetrics *metrics)
{
	PangoFontMetrics *pm;

	pm = pango_font_get_metrics(font->f, NULL);
	metrics->Ascent = pangoToCairo(pango_font_metrics_get_ascent(pm));
	metrics->Descent = pangoToCairo(pango_font_metrics_get_descent(pm));
	// Pango doesn't seem to expose this :( Use 0 and hope for the best.
	metrics->Leading = 0;
	metrics->UnderlinePos = pangoToCairo(pango_font_metrics_get_underline_position(pm));
	metrics->UnderlineThickness = pangoToCairo(pango_font_metrics_get_underline_thickness(pm));
	pango_font_metrics_unref(pm);
}
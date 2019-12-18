#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiDrawTextFontDescriptor ;
struct TYPE_3__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ uiDrawTextFont ;
typedef  int /*<<< orphan*/  PangoFontDescription ;

/* Variables and functions */
 int /*<<< orphan*/ * pango_font_describe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 

void uiDrawTextFontDescribe(uiDrawTextFont *font, uiDrawTextFontDescriptor *desc)
{
	PangoFontDescription *pdesc;

	// this creates a copy; we free it later
	pdesc = pango_font_describe(font->f);

	// TODO

	pango_font_description_free(pdesc);
}
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
struct TYPE_3__ {int /*<<< orphan*/ ** f; } ;
typedef  TYPE_1__ uiDrawFontFamilies ;
typedef  int /*<<< orphan*/  PangoFontFamily ;

/* Variables and functions */
 int /*<<< orphan*/  pango_font_family_get_name (int /*<<< orphan*/ *) ; 
 char* uiUnixStrdupText (int /*<<< orphan*/ ) ; 

char *uiDrawFontFamiliesFamily(uiDrawFontFamilies *ff, int n)
{
	PangoFontFamily *f;

	f = ff->f[n];
	return uiUnixStrdupText(pango_font_family_get_name(f));
}
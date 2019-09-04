#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ uiDrawFontFamilies ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFree (TYPE_1__*) ; 

void uiDrawFreeFontFamilies(uiDrawFontFamilies *ff)
{
	g_free(ff->f);
	uiFree(ff);
}
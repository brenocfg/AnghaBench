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
struct TYPE_4__ {int /*<<< orphan*/  s; struct TYPE_4__* graphemes; int /*<<< orphan*/  defaultFont; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ uiDrawTextLayout ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_attr_list_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFree (TYPE_1__*) ; 

void uiDrawFreeTextLayout(uiDrawTextLayout *layout)
{
	pango_attr_list_unref(layout->attrs);
	g_object_unref(layout->defaultFont);
	uiFree(layout->graphemes);
	g_free(layout->s);
	uiFree(layout);
}
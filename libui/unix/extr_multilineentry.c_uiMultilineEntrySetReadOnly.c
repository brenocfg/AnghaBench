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
struct TYPE_3__ {int /*<<< orphan*/  textview; } ;
typedef  TYPE_1__ uiMultilineEntry ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_text_view_set_editable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiMultilineEntrySetReadOnly(uiMultilineEntry *e, int readonly)
{
	gboolean editable;

	editable = TRUE;
	if (readonly)
		editable = FALSE;
	gtk_text_view_set_editable(e->textview, editable);
}
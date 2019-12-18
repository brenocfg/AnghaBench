#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiTableTextColumnOptionalParams ;
typedef  int /*<<< orphan*/  uiTable ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;

/* Variables and functions */
 int /*<<< orphan*/  addCheckboxColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * addColumn (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  addTextColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

void uiTableAppendCheckboxTextColumn(uiTable *t, const char *name, int checkboxModelColumn, int checkboxEditableModelColumn, int textModelColumn, int textEditableModelColumn, uiTableTextColumnOptionalParams *textParams)
{
	GtkTreeViewColumn *c;

	c = addColumn(t, name);
	addCheckboxColumn(t, c, checkboxModelColumn, checkboxEditableModelColumn);
	addTextColumn(t, c, textModelColumn, textEditableModelColumn, textParams);
}
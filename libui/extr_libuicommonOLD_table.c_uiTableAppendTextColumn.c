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
typedef  int /*<<< orphan*/  uiTableColumn ;
typedef  int /*<<< orphan*/  uiTable ;

/* Variables and functions */
 int /*<<< orphan*/ * uiTableAppendColumn (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  uiTableColumnAppendTextPart (int /*<<< orphan*/ *,int,int) ; 

uiTableColumn *uiTableAppendTextColumn(uiTable *t, const char *name, int modelColumn)
{
	uiTableColumn *tc;

	tc = uiTableAppendColumn(t, name);
	uiTableColumnAppendTextPart(tc, modelColumn, 1);
	return tc;
}
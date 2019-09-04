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
typedef  int /*<<< orphan*/  uiTableModelHandler ;
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/ * checkStates ; 
 int /*<<< orphan*/  row9text ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  uiTableModelTakeInt (void const*) ; 
 int yellowRow ; 

__attribute__((used)) static void modelSetCellValue(uiTableModelHandler *mh, uiTableModel *m, int row, int col, const void *val)
{
	if (row == 9 && col == 2)
		strcpy(row9text, (const char *) val);
	if (col == 6)
		yellowRow = row;
	if (col == 7)
		checkStates[row] = uiTableModelTakeInt(val);
}
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
typedef  int /*<<< orphan*/  uiTableValue ;
typedef  int /*<<< orphan*/  uiTableModelHandler ;
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/ * checkStates ; 
 int /*<<< orphan*/  row9text ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableModelRowChanged (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiTableValueInt (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uiTableValueString (int /*<<< orphan*/  const*) ; 
 int yellowRow ; 

__attribute__((used)) static void modelSetCellValue(uiTableModelHandler *mh, uiTableModel *m, int row, int col, const uiTableValue *val)
{
	if (row == 9 && col == 2)
		strcpy(row9text, uiTableValueString(val));
	if (col == 6) {
		int prevYellowRow;

		prevYellowRow = yellowRow;
		yellowRow = row;
		if (prevYellowRow != -1)
			uiTableModelRowChanged(m, prevYellowRow);
		uiTableModelRowChanged(m, yellowRow);
	}
	if (col == 7)
		checkStates[row] = uiTableValueInt(val);
}
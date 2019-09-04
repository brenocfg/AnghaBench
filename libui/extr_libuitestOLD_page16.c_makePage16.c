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
typedef  int /*<<< orphan*/  uiTableModel ;
typedef  int /*<<< orphan*/  uiTableColumn ;
typedef  int /*<<< orphan*/  uiTable ;
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_3__ {int /*<<< orphan*/  SetCellValue; int /*<<< orphan*/  CellValue; int /*<<< orphan*/  NumRows; int /*<<< orphan*/  ColumnType; int /*<<< orphan*/  NumColumns; } ;

/* Variables and functions */
 int /*<<< orphan*/  appendImageNamed (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  checkStates ; 
 int /*<<< orphan*/ * img ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ mh ; 
 int /*<<< orphan*/  modelCellValue ; 
 int /*<<< orphan*/  modelColumnType ; 
 int /*<<< orphan*/  modelNumColumns ; 
 int /*<<< orphan*/  modelNumRows ; 
 int /*<<< orphan*/  modelSetCellValue ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  row9text ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiNewImage (int,int) ; 
 int /*<<< orphan*/ * uiNewTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewTableModel (TYPE_1__*) ; 
 int /*<<< orphan*/ * uiTableAppendColumn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiTableAppendTextColumn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableColumnAppendButtonPart (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiTableColumnAppendCheckboxPart (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableColumnAppendImagePart (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableColumnAppendProgressBarPart (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableColumnAppendTextPart (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiTableColumnPartSetEditable (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiTableColumnPartSetTextColor (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiTableSetRowBackgroundColorModelColumn (int /*<<< orphan*/ *,int) ; 

uiBox *makePage16(void)
{
	uiBox *page16;
	uiTableModel *m;
	uiTable *t;
	uiTableColumn *tc;

	img[0] = uiNewImage(16, 16);
	appendImageNamed(img[0], "andlabs_16x16test_24june2016.png");
	appendImageNamed(img[0], "andlabs_32x32test_24june2016.png");
	img[1] = uiNewImage(16, 16);
	appendImageNamed(img[1], "tango-icon-theme-0.8.90_16x16_x-office-spreadsheet.png");
	appendImageNamed(img[1], "tango-icon-theme-0.8.90_32x32_x-office-spreadsheet.png");

	strcpy(row9text, "Part");

	memset(checkStates, 0, 15 * sizeof (int));

	page16 = newVerticalBox();

	mh.NumColumns = modelNumColumns;
	mh.ColumnType = modelColumnType;
	mh.NumRows = modelNumRows;
	mh.CellValue = modelCellValue;
	mh.SetCellValue = modelSetCellValue;
	m = uiNewTableModel(&mh);

	t = uiNewTable(m);
	uiBoxAppend(page16, uiControl(t), 1);

	uiTableAppendTextColumn(t, "Column 1", 0);

	tc = uiTableAppendColumn(t, "Column 2");
	uiTableColumnAppendImagePart(tc, 5, 0);
	uiTableColumnAppendTextPart(tc, 1, 0);
	uiTableColumnAppendTextPart(tc, 2, 1);
	uiTableColumnPartSetTextColor(tc, 1, 4);
	uiTableColumnPartSetEditable(tc, 2, 1);

	uiTableSetRowBackgroundColorModelColumn(t, 3);

	tc = uiTableAppendColumn(t, "Buttons");
	uiTableColumnAppendCheckboxPart(tc, 7, 0);
	uiTableColumnAppendButtonPart(tc, 6, 1);

	tc = uiTableAppendColumn(t, "Progress Bar");
	uiTableColumnAppendProgressBarPart(tc, 8, 0);

	return page16;
}
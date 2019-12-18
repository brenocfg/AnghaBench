#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int RowBackgroundColorModelColumn; int ColorModelColumn; int /*<<< orphan*/  Model; } ;
typedef  TYPE_1__ uiTableTextColumnOptionalParams ;
typedef  TYPE_1__ uiTableParams ;
typedef  int /*<<< orphan*/  uiTable ;
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_10__ {int /*<<< orphan*/  SetCellValue; int /*<<< orphan*/  CellValue; int /*<<< orphan*/  NumRows; int /*<<< orphan*/  ColumnType; int /*<<< orphan*/  NumColumns; } ;

/* Variables and functions */
 int /*<<< orphan*/  appendImageNamed (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* checkStates ; 
 int /*<<< orphan*/ * img ; 
 int /*<<< orphan*/  m ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ mh ; 
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
 int /*<<< orphan*/ * uiNewTable (TYPE_1__*) ; 
 int /*<<< orphan*/  uiNewTableModel (TYPE_4__*) ; 
 int /*<<< orphan*/  uiTableAppendButtonColumn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableAppendCheckboxColumn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTableAppendImageTextColumn (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uiTableAppendProgressBarColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  uiTableAppendTextColumn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiTableModelColumnAlwaysEditable ; 
 int /*<<< orphan*/  uiTableModelColumnNeverEditable ; 

uiBox *makePage16(void)
{
	uiBox *page16;
	uiTable *t;
	uiTableParams p;
	uiTableTextColumnOptionalParams tp;

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

	memset(&p, 0, sizeof (uiTableParams));
	p.Model = m;
	p.RowBackgroundColorModelColumn = 3;
	t = uiNewTable(&p);
	uiBoxAppend(page16, uiControl(t), 1);

	uiTableAppendTextColumn(t, "Column 1",
		0, uiTableModelColumnNeverEditable, NULL);

	memset(&tp, 0, sizeof (uiTableTextColumnOptionalParams));
	tp.ColorModelColumn = 4;
	uiTableAppendImageTextColumn(t, "Column 2",
		5,
		1, uiTableModelColumnNeverEditable, &tp);
	uiTableAppendTextColumn(t, "Editable",
		2, uiTableModelColumnAlwaysEditable, NULL);

	uiTableAppendCheckboxColumn(t, "Checkboxes",
		7, uiTableModelColumnAlwaysEditable);
	uiTableAppendButtonColumn(t, "Buttons",
		6, uiTableModelColumnAlwaysEditable);

	uiTableAppendProgressBarColumn(t, "Progress Bar",
		8);

	return page16;
}
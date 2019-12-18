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
typedef  int /*<<< orphan*/  uiTableValue ;
struct TYPE_4__ {int /*<<< orphan*/ * (* CellValue ) (TYPE_1__*,int /*<<< orphan*/ *,int,int) ;} ;
typedef  TYPE_1__ uiTableModelHandler ;
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* uiprivTableModelHandler (int /*<<< orphan*/ *) ; 

uiTableValue *uiprivTableModelCellValue(uiTableModel *m, int row, int column)
{
	uiTableModelHandler *mh;

	mh = uiprivTableModelHandler(m);
	return (*(mh->CellValue))(mh, m, row, column);
}
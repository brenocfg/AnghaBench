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
typedef  int /*<<< orphan*/  uiTableValueType ;
struct TYPE_4__ {int /*<<< orphan*/  (* ColumnType ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ uiTableModelHandler ;
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* uiprivTableModelHandler (int /*<<< orphan*/ *) ; 

uiTableValueType uiprivTableModelColumnType(uiTableModel *m, int column)
{
	uiTableModelHandler *mh;

	mh = uiprivTableModelHandler(m);
	return (*(mh->ColumnType))(mh, m, column);
}
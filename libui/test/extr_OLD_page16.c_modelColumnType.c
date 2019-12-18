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
typedef  int /*<<< orphan*/  uiTableModelColumnType ;
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/  uiTableModelColumnColor ; 
 int /*<<< orphan*/  uiTableModelColumnImage ; 
 int /*<<< orphan*/  uiTableModelColumnInt ; 
 int /*<<< orphan*/  uiTableModelColumnString ; 

__attribute__((used)) static uiTableModelColumnType modelColumnType(uiTableModelHandler *mh, uiTableModel *m, int column)
{
	if (column == 3 || column == 4)
		return uiTableModelColumnColor;
	if (column == 5)
		return uiTableModelColumnImage;
	if (column == 7 || column == 8)
		return uiTableModelColumnInt;
	return uiTableModelColumnString;
}
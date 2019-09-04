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
typedef  int /*<<< orphan*/  uiTableModel ;
typedef  int intmax_t ;

/* Variables and functions */
 void* uiTableModelFromBool (int) ; 
 void* uiTableModelFromString (char*) ; 

void *modelCellValue(uiTableModel *m, void *mData, intmax_t row, intmax_t column)
{
	char line[20];

	line[0] = 'R';
	line[1] = 'o';
	line[2] = 'w';
	line[3] = ' ';
	line[4] = row + '0';
	line[5] = '\0';
	switch (column) {
	case 0:
	case 1:
		return uiTableModelFromString(line);
	case 2:
		return uiTableModelFromBool(row % 2 == 0);
	case 3:
		return uiTableModelFromBool(row % 3 == 0);
	}
	// TODO
	return NULL;
}
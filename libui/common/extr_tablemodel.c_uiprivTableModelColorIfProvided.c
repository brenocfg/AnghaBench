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
typedef  int /*<<< orphan*/  uiTableModel ;

/* Variables and functions */
 int /*<<< orphan*/  uiFreeTableValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiTableValueColor (int /*<<< orphan*/ *,double*,double*,double*,double*) ; 
 int /*<<< orphan*/ * uiprivTableModelCellValue (int /*<<< orphan*/ *,int,int) ; 

int uiprivTableModelColorIfProvided(uiTableModel *m, int row, int column, double *r, double *g, double *b, double *a)
{
	uiTableValue *value;

	if (column == -1)
		return 0;
	value = uiprivTableModelCellValue(m, row, column);
	if (value == NULL)
		return 0;
	uiTableValueColor(value, r, g, b, a);
	uiFreeTableValue(value);
	return 1;
}
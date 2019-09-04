#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ no_column_names; } ;

/* Variables and functions */
 int DASH_COLLAPSED ; 
 int DASH_COL_ROWS ; 
 int DASH_NON_DATA ; 
 TYPE_1__ conf ; 

int
get_num_collapsed_data_rows (void)
{
  /* The default number of rows is fixed */
  int size = DASH_COLLAPSED - DASH_NON_DATA;
  /* If no column names, then add the number of rows occupied by the
   * column values to the default number */
  return conf.no_column_names ? size + DASH_COL_ROWS : size;
}
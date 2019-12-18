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
 int DASH_COL_ROWS ; 
 int DASH_DATA_POS ; 
 TYPE_1__ conf ; 

__attribute__((used)) static int
get_data_pos_rows (void)
{
  return conf.no_column_names ? DASH_DATA_POS - DASH_COL_ROWS : DASH_DATA_POS;
}
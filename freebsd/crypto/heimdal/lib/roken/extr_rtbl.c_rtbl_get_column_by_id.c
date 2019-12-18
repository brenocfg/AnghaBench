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
struct column_data {unsigned int column_id; } ;
typedef  TYPE_1__* rtbl_t ;
struct TYPE_3__ {size_t num_columns; struct column_data** columns; } ;

/* Variables and functions */

__attribute__((used)) static struct column_data *
rtbl_get_column_by_id (rtbl_t table, unsigned int id)
{
    size_t i;
    for(i = 0; i < table->num_columns; i++)
	if(table->columns[i]->column_id == id)
	    return table->columns[i];
    return NULL;
}
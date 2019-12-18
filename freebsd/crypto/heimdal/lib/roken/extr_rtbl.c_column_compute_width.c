#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct column_data {size_t num_rows; TYPE_1__* rows; scalar_t__ width; int /*<<< orphan*/  header; } ;
typedef  TYPE_2__* rtbl_t ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int RTBL_HEADER_STYLE_NONE ; 
 scalar_t__ max (scalar_t__,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
column_compute_width (rtbl_t table, struct column_data *column)
{
    size_t i;

    if(table->flags & RTBL_HEADER_STYLE_NONE)
	column->width = 0;
    else
	column->width = strlen (column->header);
    for (i = 0; i < column->num_rows; i++)
	column->width = max (column->width, (int) strlen (column->rows[i].data));
}
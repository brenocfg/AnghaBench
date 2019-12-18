#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; } ;
struct TYPE_6__ {int attr; int /*<<< orphan*/  type; TYPE_1__ value; } ;
typedef  TYPE_2__ attr_val ;

/* Variables and functions */
 int /*<<< orphan*/  T_Integer ; 
 TYPE_2__* emalloc_zero (int) ; 

attr_val *
create_attr_ival(
	int attr,
	int value
	)
{
	attr_val *my_val;

	my_val = emalloc_zero(sizeof(*my_val));
	my_val->attr = attr;
	my_val->value.i = value;
	my_val->type = T_Integer;

	return my_val;
}
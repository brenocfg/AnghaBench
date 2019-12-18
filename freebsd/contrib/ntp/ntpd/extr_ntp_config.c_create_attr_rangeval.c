#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int first; int last; } ;
struct TYPE_7__ {TYPE_1__ r; } ;
struct TYPE_8__ {int attr; int /*<<< orphan*/  type; TYPE_2__ value; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 int /*<<< orphan*/  T_Intrange ; 
 TYPE_3__* emalloc_zero (int) ; 

attr_val *
create_attr_rangeval(
	int	attr,
	int	first,
	int	last
	)
{
	attr_val *my_val;

	my_val = emalloc_zero(sizeof(*my_val));
	my_val->attr = attr;
	my_val->value.r.first = first;
	my_val->value.r.last = last;
	my_val->type = T_Intrange;

	return my_val;
}
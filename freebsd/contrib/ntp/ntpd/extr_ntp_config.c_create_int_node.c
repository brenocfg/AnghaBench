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
struct TYPE_4__ {int i; } ;
typedef  TYPE_1__ int_node ;

/* Variables and functions */
 TYPE_1__* emalloc_zero (int) ; 

int_node *
create_int_node(
	int val
	)
{
	int_node *i_n;

	i_n = emalloc_zero(sizeof(*i_n));
	i_n->i = val;

	return i_n;
}
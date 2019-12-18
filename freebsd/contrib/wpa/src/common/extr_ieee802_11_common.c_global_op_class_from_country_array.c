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
typedef  scalar_t__ u8 ;
struct country_op_class {scalar_t__ country_op_class; scalar_t__ global_op_class; } ;

/* Variables and functions */

__attribute__((used)) static u8
global_op_class_from_country_array(u8 op_class, size_t array_size,
				   const struct country_op_class *country_array)
{
	size_t i;

	for (i = 0; i < array_size; i++) {
		if (country_array[i].country_op_class == op_class)
			return country_array[i].global_op_class;
	}

	return 0;
}
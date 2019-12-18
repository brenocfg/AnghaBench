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
struct oper_class_map {scalar_t__ op_class; } ;

/* Variables and functions */
 scalar_t__ country_to_global_op_class (char const*,scalar_t__) ; 
 struct oper_class_map* global_op_class ; 

const struct oper_class_map * get_oper_class(const char *country, u8 op_class)
{
	const struct oper_class_map *op;

	if (country)
		op_class = country_to_global_op_class(country, op_class);

	op = &global_op_class[0];
	while (op->op_class && op->op_class != op_class)
		op++;

	if (!op->op_class)
		return NULL;

	return op;
}
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
struct country_op_class {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct country_op_class*) ; 
 struct country_op_class* cn_op_class ; 
 int /*<<< orphan*/  cn_op_class_cc ; 
 scalar_t__ country_match (int /*<<< orphan*/ ,char const*) ; 
 struct country_op_class* eu_op_class ; 
 int /*<<< orphan*/  eu_op_class_cc ; 
 scalar_t__ global_op_class_from_country_array (scalar_t__,size_t,struct country_op_class const*) ; 
 struct country_op_class* jp_op_class ; 
 int /*<<< orphan*/  jp_op_class_cc ; 
 struct country_op_class* us_op_class ; 
 int /*<<< orphan*/  us_op_class_cc ; 

u8 country_to_global_op_class(const char *country, u8 op_class)
{
	const struct country_op_class *country_array;
	size_t size;
	u8 g_op_class;

	if (country_match(us_op_class_cc, country)) {
		country_array = us_op_class;
		size = ARRAY_SIZE(us_op_class);
	} else if (country_match(eu_op_class_cc, country)) {
		country_array = eu_op_class;
		size = ARRAY_SIZE(eu_op_class);
	} else if (country_match(jp_op_class_cc, country)) {
		country_array = jp_op_class;
		size = ARRAY_SIZE(jp_op_class);
	} else if (country_match(cn_op_class_cc, country)) {
		country_array = cn_op_class;
		size = ARRAY_SIZE(cn_op_class);
	} else {
		/*
		 * Countries that do not match any of the above countries use
		 * global operating classes
		 */
		return op_class;
	}

	g_op_class = global_op_class_from_country_array(op_class, size,
							country_array);

	/*
	 * If the given operating class did not match any of the country's
	 * operating classes, assume that global operating class is used.
	 */
	return g_op_class ? g_op_class : op_class;
}
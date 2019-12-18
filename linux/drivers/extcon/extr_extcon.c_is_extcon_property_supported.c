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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* extcon_info ; 
 int get_extcon_type (unsigned int) ; 

__attribute__((used)) static bool is_extcon_property_supported(unsigned int id, unsigned int prop)
{
	int type;

	/* Check whether the property is supported or not. */
	type = get_extcon_type(prop);
	if (type < 0)
		return false;

	/* Check whether a specific extcon id supports the property or not. */
	return !!(extcon_info[id].type & type);
}
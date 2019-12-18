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
typedef  enum reg_type { ____Placeholder_reg_type } reg_type ;

/* Variables and functions */
#define  REGDOM_TYPE_COUNTRY 132 
#define  REGDOM_TYPE_CUSTOM_WORLD 131 
#define  REGDOM_TYPE_INTERSECTION 130 
#define  REGDOM_TYPE_UNKNOWN 129 
#define  REGDOM_TYPE_WORLD 128 

__attribute__((used)) static const char * reg_type_str(enum reg_type type)
{
	switch (type) {
	case REGDOM_TYPE_UNKNOWN:
		return "UNKNOWN";
	case REGDOM_TYPE_COUNTRY:
		return "COUNTRY";
	case REGDOM_TYPE_WORLD:
		return "WORLD";
	case REGDOM_TYPE_CUSTOM_WORLD:
		return "CUSTOM_WORLD";
	case REGDOM_TYPE_INTERSECTION:
		return "INTERSECTION";
	}
	return "?";
}
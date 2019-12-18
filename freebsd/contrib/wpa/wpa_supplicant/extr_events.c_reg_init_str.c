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
typedef  enum reg_change_initiator { ____Placeholder_reg_change_initiator } reg_change_initiator ;

/* Variables and functions */
#define  REGDOM_BEACON_HINT 132 
#define  REGDOM_SET_BY_CORE 131 
#define  REGDOM_SET_BY_COUNTRY_IE 130 
#define  REGDOM_SET_BY_DRIVER 129 
#define  REGDOM_SET_BY_USER 128 

__attribute__((used)) static const char * reg_init_str(enum reg_change_initiator init)
{
	switch (init) {
	case REGDOM_SET_BY_CORE:
		return "CORE";
	case REGDOM_SET_BY_USER:
		return "USER";
	case REGDOM_SET_BY_DRIVER:
		return "DRIVER";
	case REGDOM_SET_BY_COUNTRY_IE:
		return "COUNTRY_IE";
	case REGDOM_BEACON_HINT:
		return "BEACON_HINT";
	}
	return "?";
}
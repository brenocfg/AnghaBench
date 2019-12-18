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
typedef  enum roce_mode { ____Placeholder_roce_mode } roce_mode ;
typedef  enum roce_flavor { ____Placeholder_roce_flavor } roce_flavor ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ROCE_MODE ; 
 int PLAIN_ROCE ; 
#define  ROCE_V1 130 
#define  ROCE_V2_IPV4 129 
#define  ROCE_V2_IPV6 128 
 int RROCE_IPV4 ; 

__attribute__((used)) static enum roce_flavor ecore_roce_mode_to_flavor(enum roce_mode roce_mode)
{
	enum roce_flavor flavor;

	switch (roce_mode) {
	case ROCE_V1:
		flavor = PLAIN_ROCE;
		break;
	case ROCE_V2_IPV4:
		flavor = RROCE_IPV4;
		break;
	case ROCE_V2_IPV6:
		flavor = (enum roce_flavor)ROCE_V2_IPV6;
		break;
	default:
		flavor = (enum roce_flavor)MAX_ROCE_MODE;
		break;
	}
	return flavor;
}
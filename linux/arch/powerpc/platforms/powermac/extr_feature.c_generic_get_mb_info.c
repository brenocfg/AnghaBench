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
struct device_node {int dummy; } ;
struct TYPE_2__ {long model_id; long board_flags; char* model_name; } ;

/* Variables and functions */
 long EINVAL ; 
#define  PMAC_MB_INFO_FLAGS 130 
#define  PMAC_MB_INFO_MODEL 129 
#define  PMAC_MB_INFO_NAME 128 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long generic_get_mb_info(struct device_node *node, long param, long value)
{
	switch(param) {
		case PMAC_MB_INFO_MODEL:
			return pmac_mb.model_id;
		case PMAC_MB_INFO_FLAGS:
			return pmac_mb.board_flags;
		case PMAC_MB_INFO_NAME:
			/* hack hack hack... but should work */
			*((const char **)value) = pmac_mb.model_name;
			return 0;
	}
	return -EINVAL;
}
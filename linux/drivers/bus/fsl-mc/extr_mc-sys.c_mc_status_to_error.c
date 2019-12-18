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
typedef  scalar_t__ u32 ;
typedef  enum mc_cmd_status { ____Placeholder_mc_cmd_status } mc_cmd_status ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int const*) ; 
#define  EACCES 148 
#define  EBUSY 147 
 int EINVAL ; 
#define  EIO 146 
#define  ENAVAIL 145 
#define  ENODEV 144 
#define  ENOMEM 143 
#define  ENOTSUPP 142 
#define  ENXIO 141 
#define  EPERM 140 
#define  ETIMEDOUT 139 
#define  MC_CMD_STATUS_AUTH_ERR 138 
#define  MC_CMD_STATUS_BUSY 137 
#define  MC_CMD_STATUS_CONFIG_ERR 136 
#define  MC_CMD_STATUS_DMA_ERR 135 
#define  MC_CMD_STATUS_INVALID_STATE 134 
#define  MC_CMD_STATUS_NO_MEMORY 133 
#define  MC_CMD_STATUS_NO_PRIVILEGE 132 
#define  MC_CMD_STATUS_NO_RESOURCE 131 
#define  MC_CMD_STATUS_OK 130 
#define  MC_CMD_STATUS_TIMEOUT 129 
#define  MC_CMD_STATUS_UNSUPPORTED_OP 128 

__attribute__((used)) static int mc_status_to_error(enum mc_cmd_status status)
{
	static const int mc_status_to_error_map[] = {
		[MC_CMD_STATUS_OK] = 0,
		[MC_CMD_STATUS_AUTH_ERR] = -EACCES,
		[MC_CMD_STATUS_NO_PRIVILEGE] = -EPERM,
		[MC_CMD_STATUS_DMA_ERR] = -EIO,
		[MC_CMD_STATUS_CONFIG_ERR] = -ENXIO,
		[MC_CMD_STATUS_TIMEOUT] = -ETIMEDOUT,
		[MC_CMD_STATUS_NO_RESOURCE] = -ENAVAIL,
		[MC_CMD_STATUS_NO_MEMORY] = -ENOMEM,
		[MC_CMD_STATUS_BUSY] = -EBUSY,
		[MC_CMD_STATUS_UNSUPPORTED_OP] = -ENOTSUPP,
		[MC_CMD_STATUS_INVALID_STATE] = -ENODEV,
	};

	if ((u32)status >= ARRAY_SIZE(mc_status_to_error_map))
		return -EINVAL;

	return mc_status_to_error_map[status];
}
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
typedef  enum mc_cmd_status { ____Placeholder_mc_cmd_status } mc_cmd_status ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
#define  MC_CMD_STATUS_AUTH_ERR 139 
#define  MC_CMD_STATUS_BUSY 138 
#define  MC_CMD_STATUS_CONFIG_ERR 137 
#define  MC_CMD_STATUS_DMA_ERR 136 
#define  MC_CMD_STATUS_INVALID_STATE 135 
#define  MC_CMD_STATUS_NO_MEMORY 134 
#define  MC_CMD_STATUS_NO_PRIVILEGE 133 
#define  MC_CMD_STATUS_NO_RESOURCE 132 
#define  MC_CMD_STATUS_OK 131 
#define  MC_CMD_STATUS_READY 130 
#define  MC_CMD_STATUS_TIMEOUT 129 
#define  MC_CMD_STATUS_UNSUPPORTED_OP 128 

__attribute__((used)) static const char *mc_status_to_string(enum mc_cmd_status status)
{
	static const char *const status_strings[] = {
		[MC_CMD_STATUS_OK] = "Command completed successfully",
		[MC_CMD_STATUS_READY] = "Command ready to be processed",
		[MC_CMD_STATUS_AUTH_ERR] = "Authentication error",
		[MC_CMD_STATUS_NO_PRIVILEGE] = "No privilege",
		[MC_CMD_STATUS_DMA_ERR] = "DMA or I/O error",
		[MC_CMD_STATUS_CONFIG_ERR] = "Configuration error",
		[MC_CMD_STATUS_TIMEOUT] = "Operation timed out",
		[MC_CMD_STATUS_NO_RESOURCE] = "No resources",
		[MC_CMD_STATUS_NO_MEMORY] = "No memory available",
		[MC_CMD_STATUS_BUSY] = "Device is busy",
		[MC_CMD_STATUS_UNSUPPORTED_OP] = "Unsupported operation",
		[MC_CMD_STATUS_INVALID_STATE] = "Invalid state"
	};

	if ((unsigned int)status >= ARRAY_SIZE(status_strings))
		return "Unknown MC error";

	return status_strings[status];
}
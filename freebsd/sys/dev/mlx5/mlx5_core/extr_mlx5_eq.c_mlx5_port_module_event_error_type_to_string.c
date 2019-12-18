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
typedef  int u8 ;

/* Variables and functions */
#define  MLX5_MODULE_EVENT_ERROR_BUS_STUCK 135 
#define  MLX5_MODULE_EVENT_ERROR_CABLE_IS_SHORTED 134 
#define  MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST 133 
#define  MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE 132 
#define  MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX_CABLE_MODULE 131 
#define  MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT 130 
#define  MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED 129 
#define  MLX5_MODULE_EVENT_ERROR_UNSUPPORTED_CABLE 128 

__attribute__((used)) static const char *mlx5_port_module_event_error_type_to_string(u8 error_type)
{
	switch (error_type) {
	case MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED:
		return "Power budget exceeded";
	case MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX_CABLE_MODULE:
		return "Long Range for non MLNX cable";
	case MLX5_MODULE_EVENT_ERROR_BUS_STUCK:
		return "Bus stuck(I2C or data shorted)";
	case MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT:
		return "No EEPROM/retry timeout";
	case MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST:
		return "Enforce part number list";
	case MLX5_MODULE_EVENT_ERROR_UNSUPPORTED_CABLE:
		return "Unknown identifier";
	case MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE:
		return "High Temperature";
	case MLX5_MODULE_EVENT_ERROR_CABLE_IS_SHORTED:
		return "Bad or shorted cable/module";
	default:
		return "Unknown error type";
	}
}
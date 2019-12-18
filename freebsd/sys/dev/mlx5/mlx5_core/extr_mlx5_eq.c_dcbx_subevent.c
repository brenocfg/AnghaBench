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
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
#define  MLX5_DCBX_EVENT_SUBTYPE_ERROR_STATE_DCBX 131 
#define  MLX5_DCBX_EVENT_SUBTYPE_LOCAL_OPER_CHANGE 130 
#define  MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_APP_PRIORITY_CHANGE 129 
#define  MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_CHANGE 128 
 int MLX5_DEV_EVENT_ERROR_STATE_DCBX ; 
 int MLX5_DEV_EVENT_LOCAL_OPER_CHANGE ; 
 int MLX5_DEV_EVENT_REMOTE_CONFIG_APPLICATION_PRIORITY_CHANGE ; 
 int MLX5_DEV_EVENT_REMOTE_CONFIG_CHANGE ; 

__attribute__((used)) static enum mlx5_dev_event dcbx_subevent(u8 subtype)
{
	switch (subtype) {
	case MLX5_DCBX_EVENT_SUBTYPE_ERROR_STATE_DCBX:
		return MLX5_DEV_EVENT_ERROR_STATE_DCBX;
	case MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_CHANGE:
		return MLX5_DEV_EVENT_REMOTE_CONFIG_CHANGE;
	case MLX5_DCBX_EVENT_SUBTYPE_LOCAL_OPER_CHANGE:
		return MLX5_DEV_EVENT_LOCAL_OPER_CHANGE;
	case MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_APP_PRIORITY_CHANGE:
		return MLX5_DEV_EVENT_REMOTE_CONFIG_APPLICATION_PRIORITY_CHANGE;
	}
	return -1;
}
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

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOSPC ; 
#define  ERST_STATUS_HARDWARE_NOT_AVAILABLE 132 
#define  ERST_STATUS_NOT_ENOUGH_SPACE 131 
#define  ERST_STATUS_RECORD_NOT_FOUND 130 
#define  ERST_STATUS_RECORD_STORE_EMPTY 129 
#define  ERST_STATUS_SUCCESS 128 

__attribute__((used)) static inline int erst_errno(int command_status)
{
	switch (command_status) {
	case ERST_STATUS_SUCCESS:
		return 0;
	case ERST_STATUS_HARDWARE_NOT_AVAILABLE:
		return -ENODEV;
	case ERST_STATUS_NOT_ENOUGH_SPACE:
		return -ENOSPC;
	case ERST_STATUS_RECORD_STORE_EMPTY:
	case ERST_STATUS_RECORD_NOT_FOUND:
		return -ENOENT;
	default:
		return -EINVAL;
	}
}
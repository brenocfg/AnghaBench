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
 int EIO ; 
 int SCMI_ERR_MAX ; 
 int SCMI_SUCCESS ; 
 int* scmi_linux_errmap ; 

__attribute__((used)) static inline int scmi_to_linux_errno(int errno)
{
	if (errno < SCMI_SUCCESS && errno > SCMI_ERR_MAX)
		return scmi_linux_errmap[-errno];
	return -EIO;
}
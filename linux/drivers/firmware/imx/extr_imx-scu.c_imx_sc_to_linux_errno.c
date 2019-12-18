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
 int IMX_SC_ERR_LAST ; 
 int IMX_SC_ERR_NONE ; 
 int* imx_sc_linux_errmap ; 

__attribute__((used)) static inline int imx_sc_to_linux_errno(int errno)
{
	if (errno >= IMX_SC_ERR_NONE && errno < IMX_SC_ERR_LAST)
		return imx_sc_linux_errmap[errno];
	return -EIO;
}
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
struct imx_sc_ipc {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 struct imx_sc_ipc* imx_sc_ipc_handle ; 

int imx_scu_get_handle(struct imx_sc_ipc **ipc)
{
	if (!imx_sc_ipc_handle)
		return -EPROBE_DEFER;

	*ipc = imx_sc_ipc_handle;
	return 0;
}
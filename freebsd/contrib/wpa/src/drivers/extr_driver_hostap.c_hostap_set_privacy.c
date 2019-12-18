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
struct hostap_drvier_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRISM2_PARAM_PRIVACY_INVOKED ; 
 int hostap_ioctl_prism2param (struct hostap_drvier_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hostap_set_privacy(void *priv, int enabled)
{
	struct hostap_drvier_data *drv = priv;

	return hostap_ioctl_prism2param(drv, PRISM2_PARAM_PRIVACY_INVOKED,
					enabled);
}
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
struct wpa_bss_params {int enabled; } ;
struct hostap_driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRISM2_PARAM_HOST_DECRYPT ; 
 int /*<<< orphan*/  PRISM2_PARAM_HOST_ENCRYPT ; 
 int /*<<< orphan*/  PRISM2_PARAM_IEEE_802_1X ; 
 scalar_t__ hostap_ioctl_prism2param (struct hostap_driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int hostap_set_ieee8021x(void *priv, struct wpa_bss_params *params)
{
	struct hostap_driver_data *drv = priv;
	int enabled = params->enabled;

	/* enable kernel driver support for IEEE 802.1X */
	if (hostap_ioctl_prism2param(drv, PRISM2_PARAM_IEEE_802_1X, enabled)) {
		printf("Could not setup IEEE 802.1X support in kernel driver."
		       "\n");
		return -1;
	}

	if (!enabled)
		return 0;

	/* use host driver implementation of encryption to allow
	 * individual keys and passing plaintext EAPOL frames */
	if (hostap_ioctl_prism2param(drv, PRISM2_PARAM_HOST_DECRYPT, 1) ||
	    hostap_ioctl_prism2param(drv, PRISM2_PARAM_HOST_ENCRYPT, 1)) {
		printf("Could not setup host-based encryption in kernel "
		       "driver.\n");
		return -1;
	}

	return 0;
}
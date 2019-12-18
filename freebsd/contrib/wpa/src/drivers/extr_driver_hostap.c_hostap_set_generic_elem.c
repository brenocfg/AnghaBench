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
typedef  int /*<<< orphan*/  u8 ;
struct hostap_driver_data {size_t generic_ie_len; int /*<<< orphan*/ * generic_ie; } ;

/* Variables and functions */
 int hostapd_ioctl_set_generic_elem (struct hostap_driver_data*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int hostap_set_generic_elem(void *priv,
				   const u8 *elem, size_t elem_len)
{
	struct hostap_driver_data *drv = priv;

	os_free(drv->generic_ie);
	drv->generic_ie = NULL;
	drv->generic_ie_len = 0;
	if (elem) {
		drv->generic_ie = os_memdup(elem, elem_len);
		if (drv->generic_ie == NULL)
			return -1;
		drv->generic_ie_len = elem_len;
	}

	return hostapd_ioctl_set_generic_elem(drv);
}
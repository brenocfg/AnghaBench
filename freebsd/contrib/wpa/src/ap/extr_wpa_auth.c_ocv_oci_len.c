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
struct wpa_state_machine {int dummy; } ;

/* Variables and functions */
 int OCV_OCI_KDE_LEN ; 
 scalar_t__ wpa_auth_uses_ocv (struct wpa_state_machine*) ; 

__attribute__((used)) static int ocv_oci_len(struct wpa_state_machine *sm)
{
#ifdef CONFIG_OCV
	if (wpa_auth_uses_ocv(sm))
		return OCV_OCI_KDE_LEN;
#endif /* CONFIG_OCV */
	return 0;
}
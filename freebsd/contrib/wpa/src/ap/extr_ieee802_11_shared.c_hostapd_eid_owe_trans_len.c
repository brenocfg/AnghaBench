#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {size_t owe_transition_ssid_len; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  hostapd_eid_owe_trans_enabled (struct hostapd_data*) ; 

size_t hostapd_eid_owe_trans_len(struct hostapd_data *hapd)
{
#ifdef CONFIG_OWE
	if (!hostapd_eid_owe_trans_enabled(hapd))
		return 0;
	return 6 + ETH_ALEN + 1 + hapd->conf->owe_transition_ssid_len;
#else /* CONFIG_OWE */
	return 0;
#endif /* CONFIG_OWE */
}
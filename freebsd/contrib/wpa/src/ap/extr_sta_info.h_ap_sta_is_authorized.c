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
struct sta_info {int flags; } ;

/* Variables and functions */
 int WLAN_STA_AUTHORIZED ; 

__attribute__((used)) static inline int ap_sta_is_authorized(struct sta_info *sta)
{
	return sta->flags & WLAN_STA_AUTHORIZED;
}
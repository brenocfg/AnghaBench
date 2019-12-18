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
struct os_reltime {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_acl_expire_cache (struct hostapd_data*,struct os_reltime*) ; 
 int /*<<< orphan*/  hostapd_acl_expire_queries (struct hostapd_data*,struct os_reltime*) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 

void hostapd_acl_expire(struct hostapd_data *hapd)
{
	struct os_reltime now;

	os_get_reltime(&now);
	hostapd_acl_expire_cache(hapd, &now);
	hostapd_acl_expire_queries(hapd, &now);
}
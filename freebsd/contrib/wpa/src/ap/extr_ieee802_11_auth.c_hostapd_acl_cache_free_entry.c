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
struct hostapd_cached_radius_acl {int /*<<< orphan*/  psk; struct hostapd_cached_radius_acl* radius_cui; struct hostapd_cached_radius_acl* identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_free_psk_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct hostapd_cached_radius_acl*) ; 

__attribute__((used)) static void hostapd_acl_cache_free_entry(struct hostapd_cached_radius_acl *e)
{
	os_free(e->identity);
	os_free(e->radius_cui);
	hostapd_free_psk_list(e->psk);
	os_free(e);
}
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
struct hostapd_cached_radius_acl {struct hostapd_cached_radius_acl* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_acl_cache_free_entry (struct hostapd_cached_radius_acl*) ; 

__attribute__((used)) static void hostapd_acl_cache_free(struct hostapd_cached_radius_acl *acl_cache)
{
	struct hostapd_cached_radius_acl *prev;

	while (acl_cache) {
		prev = acl_cache;
		acl_cache = acl_cache->next;
		hostapd_acl_cache_free_entry(prev);
	}
}
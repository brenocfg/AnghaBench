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
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  radius_class; int /*<<< orphan*/  cui; int /*<<< orphan*/  identity; int /*<<< orphan*/  vlan_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct rsn_pmksa_cache_entry*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_free_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _pmksa_cache_free_entry(struct rsn_pmksa_cache_entry *entry)
{
	os_free(entry->vlan_desc);
	os_free(entry->identity);
	wpabuf_free(entry->cui);
#ifndef CONFIG_NO_RADIUS
	radius_free_class(&entry->radius_class);
#endif /* CONFIG_NO_RADIUS */
	bin_clear_free(entry, sizeof(*entry));
}
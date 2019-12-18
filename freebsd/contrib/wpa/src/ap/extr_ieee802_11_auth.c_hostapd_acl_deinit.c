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
struct hostapd_data {struct hostapd_acl_query_data* acl_queries; int /*<<< orphan*/ * acl_cache; } ;
struct hostapd_acl_query_data {struct hostapd_acl_query_data* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_acl_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_acl_query_free (struct hostapd_acl_query_data*) ; 

void hostapd_acl_deinit(struct hostapd_data *hapd)
{
	struct hostapd_acl_query_data *query, *prev;

#ifndef CONFIG_NO_RADIUS
	hostapd_acl_cache_free(hapd->acl_cache);
	hapd->acl_cache = NULL;
#endif /* CONFIG_NO_RADIUS */

	query = hapd->acl_queries;
	hapd->acl_queries = NULL;
	while (query) {
		prev = query;
		query = query->next;
		hostapd_acl_query_free(prev);
	}
}
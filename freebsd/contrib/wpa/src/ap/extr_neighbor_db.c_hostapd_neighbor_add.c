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
struct hostapd_neighbor_entry {int /*<<< orphan*/  list; } ;
struct hostapd_data {int /*<<< orphan*/  nr_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hostapd_neighbor_entry* os_zalloc (int) ; 

__attribute__((used)) static struct hostapd_neighbor_entry *
hostapd_neighbor_add(struct hostapd_data *hapd)
{
	struct hostapd_neighbor_entry *nr;

	nr = os_zalloc(sizeof(struct hostapd_neighbor_entry));
	if (!nr)
		return NULL;

	dl_list_add(&hapd->nr_db, &nr->list);

	return nr;
}
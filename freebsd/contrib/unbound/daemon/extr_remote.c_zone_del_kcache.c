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
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct key_entry_key {int /*<<< orphan*/  name; } ;
struct key_entry_data {scalar_t__ ttl; } ;
struct del_info {scalar_t__ expired; int /*<<< orphan*/  num_keys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zone_del_kcache(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct key_entry_key* k = (struct key_entry_key*)e->key;
	if(dname_subdomain_c(k->name, inf->name)) {
		struct key_entry_data* d = (struct key_entry_data*)e->data;
		if(d->ttl > inf->expired) {
			d->ttl = inf->expired;
			inf->num_keys++;
		}
	}
}
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
struct lruhash_entry {scalar_t__ data; } ;
struct key_entry_data {int /*<<< orphan*/  ttl; scalar_t__ isbad; } ;
struct del_info {int /*<<< orphan*/  num_keys; int /*<<< orphan*/  expired; } ;

/* Variables and functions */

__attribute__((used)) static void
negative_del_kcache(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct key_entry_data* d = (struct key_entry_data*)e->data;
	/* could be bad because of lookup failure on the DS, DNSKEY, which
	 * was nxdomain or servfail, and thus a result of negative lookups */
	if(d->isbad) {
		d->ttl = inf->expired;
		inf->num_keys++;
	}
}
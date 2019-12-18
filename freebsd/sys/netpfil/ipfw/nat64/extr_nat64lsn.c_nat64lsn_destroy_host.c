#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nat64lsn_host {int /*<<< orphan*/  states_hash; TYPE_1__* alias; int /*<<< orphan*/  aliases; } ;
struct nat64lsn_aliaslink {int /*<<< orphan*/  states_hash; TYPE_1__* alias; int /*<<< orphan*/  aliases; } ;
struct TYPE_3__ {int /*<<< orphan*/  hosts_count; int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ALIAS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct nat64lsn_host* CK_SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_SLIST_REMOVE (int /*<<< orphan*/ *,struct nat64lsn_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CK_SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_LOCK_DESTROY (struct nat64lsn_host*) ; 
 int /*<<< orphan*/  M_NAT64LSN ; 
 int /*<<< orphan*/  alias_entries ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_entries ; 
 int /*<<< orphan*/  nat64lsn_aliaslink ; 
 int /*<<< orphan*/  nat64lsn_aliaslink_zone ; 
 int /*<<< orphan*/  nat64lsn_host_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct nat64lsn_host*) ; 

__attribute__((used)) static void
nat64lsn_destroy_host(struct nat64lsn_host *host)
{
	struct nat64lsn_aliaslink *link;

	while (!CK_SLIST_EMPTY(&host->aliases)) {
		link = CK_SLIST_FIRST(&host->aliases);
		CK_SLIST_REMOVE_HEAD(&host->aliases, host_entries);

		ALIAS_LOCK(link->alias);
		CK_SLIST_REMOVE(&link->alias->hosts, link,
		    nat64lsn_aliaslink, alias_entries);
		link->alias->hosts_count--;
		ALIAS_UNLOCK(link->alias);

		uma_zfree(nat64lsn_aliaslink_zone, link);
	}
	HOST_LOCK_DESTROY(host);
	free(host->states_hash, M_NAT64LSN);
	uma_zfree(nat64lsn_host_zone, host);
}
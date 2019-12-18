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
struct nat64lsn_pg {int dummy; } ;
struct nat64lsn_cfg {int dummy; } ;
struct nat64lsn_alias {int /*<<< orphan*/ * icmp; int /*<<< orphan*/  icmp_chunkmask; int /*<<< orphan*/ * udp; int /*<<< orphan*/  udp_chunkmask; int /*<<< orphan*/ * tcp; int /*<<< orphan*/  tcp_chunkmask; int /*<<< orphan*/  portgroups; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_LOCK_DESTROY (struct nat64lsn_alias*) ; 
 int /*<<< orphan*/  CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct nat64lsn_pg* CK_SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  nat64lsn_destroy_pg (struct nat64lsn_pg*) ; 
 int /*<<< orphan*/  nat64lsn_pgchunk_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nat64lsn_destroy_alias(struct nat64lsn_cfg *cfg,
    struct nat64lsn_alias *alias)
{
	struct nat64lsn_pg *pg;
	int i;

	while (!CK_SLIST_EMPTY(&alias->portgroups)) {
		pg = CK_SLIST_FIRST(&alias->portgroups);
		CK_SLIST_REMOVE_HEAD(&alias->portgroups, entries);
		nat64lsn_destroy_pg(pg);
	}
	for (i = 0; i < 32; i++) {
		if (ISSET32(alias->tcp_chunkmask, i))
			uma_zfree(nat64lsn_pgchunk_zone, alias->tcp[i]);
		if (ISSET32(alias->udp_chunkmask, i))
			uma_zfree(nat64lsn_pgchunk_zone, alias->udp[i]);
		if (ISSET32(alias->icmp_chunkmask, i))
			uma_zfree(nat64lsn_pgchunk_zone, alias->icmp[i]);
	}
	ALIAS_LOCK_DESTROY(alias);
}
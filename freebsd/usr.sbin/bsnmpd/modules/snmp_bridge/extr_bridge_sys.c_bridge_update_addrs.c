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
typedef  int uint32_t ;
struct tp_entry {int flags; } ;
struct ifbareq {int /*<<< orphan*/  ifba_dst; } ;
struct bridge_if {int /*<<< orphan*/  addrs_age; } ;
typedef  int int32_t ;

/* Variables and functions */
 int BA_FOUND ; 
 struct tp_entry* bridge_addrs_bif_first (struct bridge_if*) ; 
 struct tp_entry* bridge_addrs_bif_next (struct tp_entry*) ; 
 struct tp_entry* bridge_addrs_find (int /*<<< orphan*/ ,struct bridge_if*) ; 
 int bridge_addrs_getinfo_ifalist (struct bridge_if*,struct ifbareq**) ; 
 int /*<<< orphan*/  bridge_addrs_info_ifaddrlist (struct ifbareq*,struct tp_entry*) ; 
 int /*<<< orphan*/  bridge_addrs_remove (struct tp_entry*,struct bridge_if*) ; 
 struct tp_entry* bridge_new_addrs (int /*<<< orphan*/ ,struct bridge_if*) ; 
 int /*<<< orphan*/  free (struct ifbareq*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int
bridge_update_addrs(struct bridge_if *bif)
{
	int added, updated;
	uint32_t i;
	int32_t buf_len;
	struct tp_entry *te, *te_next;
	struct ifbareq *addr_req_buf, *addr_req;

	if ((buf_len = bridge_addrs_getinfo_ifalist(bif, &addr_req_buf)) < 0)
		return (-1);

	added = updated = 0;

#define	BA_FOUND	0x01
	for (i = 0; i < buf_len / sizeof(struct ifbareq); i++) {
		addr_req = addr_req_buf + i;

		if ((te = bridge_addrs_find(addr_req->ifba_dst, bif)) == NULL) {
			added++;

			if ((te = bridge_new_addrs(addr_req->ifba_dst, bif))
			    == NULL)
				continue;
		} else
			updated++;

		bridge_addrs_info_ifaddrlist(addr_req, te);
		te-> flags |= BA_FOUND;
	}
	free(addr_req_buf);

	for (te = bridge_addrs_bif_first(bif); te != NULL; te = te_next) {
		te_next = bridge_addrs_bif_next(te);

		if ((te-> flags & BA_FOUND) == 0)
			bridge_addrs_remove(te, bif);
		else
			te-> flags &= ~BA_FOUND;
	}
#undef	BA_FOUND

	bif->addrs_age = time(NULL);
	return (updated + added);
}
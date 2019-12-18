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
struct tp_entry {int dummy; } ;
struct ifbareq {int /*<<< orphan*/  ifba_dst; } ;
struct bridge_if {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int bridge_addrs_getinfo_ifalist (struct bridge_if*,struct ifbareq**) ; 
 int /*<<< orphan*/  bridge_addrs_info_ifaddrlist (struct ifbareq*,struct tp_entry*) ; 
 struct tp_entry* bridge_new_addrs (int /*<<< orphan*/ ,struct bridge_if*) ; 
 int /*<<< orphan*/  free (struct ifbareq*) ; 

int
bridge_getinfo_bif_addrs(struct bridge_if *bif)
{
	uint32_t i;
	int32_t buf_len;
	struct ifbareq *addr_req_buf, *addr_req;
	struct tp_entry *te;

	if ((buf_len = bridge_addrs_getinfo_ifalist(bif, &addr_req_buf)) < 0)
		return (-1);

	for (i = 0; i < buf_len / sizeof(struct ifbareq); i++) {
		addr_req = addr_req_buf + i;

		if ((te = bridge_new_addrs(addr_req->ifba_dst, bif)) != NULL)
			bridge_addrs_info_ifaddrlist(addr_req, te);
	}

	free(addr_req_buf);
	return (i);
}
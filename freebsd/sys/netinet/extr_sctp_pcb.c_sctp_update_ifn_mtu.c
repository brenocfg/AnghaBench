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
typedef  int /*<<< orphan*/  uint32_t ;
struct sctp_ifn {int /*<<< orphan*/  ifn_mtu; } ;

/* Variables and functions */
 struct sctp_ifn* sctp_find_ifn (void*,int /*<<< orphan*/ ) ; 

void
sctp_update_ifn_mtu(uint32_t ifn_index, uint32_t mtu)
{
	struct sctp_ifn *sctp_ifnp;

	sctp_ifnp = sctp_find_ifn((void *)NULL, ifn_index);
	if (sctp_ifnp != NULL) {
		sctp_ifnp->ifn_mtu = mtu;
	}
}
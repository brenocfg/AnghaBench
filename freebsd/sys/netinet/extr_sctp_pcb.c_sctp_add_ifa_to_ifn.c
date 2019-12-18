#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sctp_ifn {int ifa_count; int registered_af; int /*<<< orphan*/  ifn_index; int /*<<< orphan*/  num_v6; int /*<<< orphan*/  num_v4; int /*<<< orphan*/  refcount; int /*<<< orphan*/  ifalist; } ;
struct TYPE_3__ {int sa_family; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;
struct sctp_ifa {TYPE_2__ address; struct sctp_ifn* ifn_p; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sctp_ifa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_REGISTER_INTERFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next_ifa ; 

__attribute__((used)) static void
sctp_add_ifa_to_ifn(struct sctp_ifn *sctp_ifnp, struct sctp_ifa *sctp_ifap)
{
	int ifa_af;

	LIST_INSERT_HEAD(&sctp_ifnp->ifalist, sctp_ifap, next_ifa);
	sctp_ifap->ifn_p = sctp_ifnp;
	atomic_add_int(&sctp_ifap->ifn_p->refcount, 1);
	/* update address counts */
	sctp_ifnp->ifa_count++;
	ifa_af = sctp_ifap->address.sa.sa_family;
	switch (ifa_af) {
#ifdef INET
	case AF_INET:
		sctp_ifnp->num_v4++;
		break;
#endif
#ifdef INET6
	case AF_INET6:
		sctp_ifnp->num_v6++;
		break;
#endif
	default:
		break;
	}
	if (sctp_ifnp->ifa_count == 1) {
		/* register the new interface */
		SCTP_REGISTER_INTERFACE(sctp_ifnp->ifn_index, ifa_af);
		sctp_ifnp->registered_af = ifa_af;
	}
}
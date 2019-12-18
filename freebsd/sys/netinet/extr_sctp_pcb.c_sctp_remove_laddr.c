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
struct sctp_laddr {int /*<<< orphan*/  ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct sctp_laddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_BASE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DECR_LADDR_COUNT () ; 
 int /*<<< orphan*/  SCTP_ZONE_FREE (int /*<<< orphan*/ ,struct sctp_laddr*) ; 
 int /*<<< orphan*/  ipi_zone_laddr ; 
 int /*<<< orphan*/  sctp_free_ifa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_nxt_addr ; 

__attribute__((used)) static void
sctp_remove_laddr(struct sctp_laddr *laddr)
{

	/* remove from the list */
	LIST_REMOVE(laddr, sctp_nxt_addr);
	sctp_free_ifa(laddr->ifa);
	SCTP_ZONE_FREE(SCTP_BASE_INFO(ipi_zone_laddr), laddr);
	SCTP_DECR_LADDR_COUNT();
}
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
struct lacp_peerinfo {int /*<<< orphan*/  lip_key; int /*<<< orphan*/  lip_systemid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct lacp_peerinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lacp_fill_aggregator_id_peer(struct lacp_peerinfo *lpi_aggr,
    const struct lacp_peerinfo *lpi_port)
{
	memset(lpi_aggr, 0, sizeof(*lpi_aggr));
	lpi_aggr->lip_systemid = lpi_port->lip_systemid;
	lpi_aggr->lip_key = lpi_port->lip_key;
}
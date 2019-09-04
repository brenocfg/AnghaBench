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
struct transport {scalar_t__ pack_lockfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (scalar_t__) ; 
 int /*<<< orphan*/  unlink_or_warn (scalar_t__) ; 

void transport_unlock_pack(struct transport *transport)
{
	if (transport->pack_lockfile) {
		unlink_or_warn(transport->pack_lockfile);
		FREE_AND_NULL(transport->pack_lockfile);
	}
}
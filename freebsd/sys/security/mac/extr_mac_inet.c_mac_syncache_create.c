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
struct label {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct label*,struct inpcb*) ; 
 int /*<<< orphan*/  syncache_create ; 

void
mac_syncache_create(struct label *label, struct inpcb *inp)
{

	INP_WLOCK_ASSERT(inp);

	MAC_POLICY_PERFORM_NOSLEEP(syncache_create, label, inp);
}
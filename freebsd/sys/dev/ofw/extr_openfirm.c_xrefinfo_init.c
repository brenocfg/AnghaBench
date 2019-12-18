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

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xref_init_done ; 
 int /*<<< orphan*/  xrefinfo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xreflist_lock ; 

__attribute__((used)) static void
xrefinfo_init(void *unsed)
{

	/*
	 * There is no locking during this init because it runs much earlier
	 * than any of the clients/consumers of the xref list data, but we do
	 * initialize the mutex that will be used for access later.
	 */
	mtx_init(&xreflist_lock, "OF xreflist lock", NULL, MTX_DEF);
	xrefinfo_create(OF_peer(0));
	xref_init_done = true;
}
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
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODVERSION_STR ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_SIFTR ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  SIFTR_EXPECTED_MAX_TCP_FLOWS ; 
 int /*<<< orphan*/  counter_hash ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  siftr_hashmask ; 
 int /*<<< orphan*/  siftr_pkt_mgr_mtx ; 
 int /*<<< orphan*/  siftr_pkt_queue_mtx ; 
 int /*<<< orphan*/  siftr_shutdown_handler ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_siftr(void)
{
	EVENTHANDLER_REGISTER(shutdown_pre_sync, siftr_shutdown_handler, NULL,
	    SHUTDOWN_PRI_FIRST);

	/* Initialise our flow counter hash table. */
	counter_hash = hashinit(SIFTR_EXPECTED_MAX_TCP_FLOWS, M_SIFTR,
	    &siftr_hashmask);

	mtx_init(&siftr_pkt_queue_mtx, "siftr_pkt_queue_mtx", NULL, MTX_DEF);
	mtx_init(&siftr_pkt_mgr_mtx, "siftr_pkt_mgr_mtx", NULL, MTX_DEF);

	/* Print message to the user's current terminal. */
	uprintf("\nStatistical Information For TCP Research (SIFTR) %s\n"
	    "          http://caia.swin.edu.au/urp/newtcp\n\n",
	    MODVERSION_STR);

	return (0);
}
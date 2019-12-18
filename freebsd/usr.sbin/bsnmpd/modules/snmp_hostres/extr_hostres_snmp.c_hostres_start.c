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
 int /*<<< orphan*/  HRDBG (char*) ; 
 int /*<<< orphan*/  host_registration_id ; 
 int /*<<< orphan*/  hostres_module ; 
 int /*<<< orphan*/  oid_host ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_device_tbl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_network_tbl () ; 
 int /*<<< orphan*/  start_processor_tbl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hostres_start(void)
{

	host_registration_id = or_register(&oid_host,
	    "The MIB module for Host Resource MIB (RFC 2790).",
	    hostres_module);

	start_device_tbl(hostres_module);
	start_processor_tbl(hostres_module);
	start_network_tbl();

	HRDBG("done.");
}
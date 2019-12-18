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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * memstat_mtl_alloc () ; 
 int /*<<< orphan*/ * mt_list ; 
 int /*<<< orphan*/  refresh_storage_tbl (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
init_storage_tbl(void)
{
	if ((mt_list = memstat_mtl_alloc()) == NULL)
		syslog(LOG_ERR,
		    "hrStorageTable: memstat_mtl_alloc() failed: %m");

	refresh_storage_tbl(1);
}
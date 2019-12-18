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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
aac_disk_probe(device_t dev)
{

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	return (0);
}
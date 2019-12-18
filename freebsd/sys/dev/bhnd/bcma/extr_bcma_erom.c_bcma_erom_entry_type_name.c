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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
#define  BCMA_EROM_ENTRY_TYPE_CORE 130 
#define  BCMA_EROM_ENTRY_TYPE_MPORT 129 
#define  BCMA_EROM_ENTRY_TYPE_REGION 128 
 int BCMA_EROM_GET_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRY_TYPE ; 

__attribute__((used)) static const char *
bcma_erom_entry_type_name (uint8_t entry)
{
	switch (BCMA_EROM_GET_ATTR(entry, ENTRY_TYPE)) {
	case BCMA_EROM_ENTRY_TYPE_CORE:
		return "core";
	case BCMA_EROM_ENTRY_TYPE_MPORT:
		return "mport";
	case BCMA_EROM_ENTRY_TYPE_REGION:
		return "region";
	default:
		return "unknown";
	}
}
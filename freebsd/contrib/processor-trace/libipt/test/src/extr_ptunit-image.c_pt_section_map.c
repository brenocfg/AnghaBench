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
typedef  scalar_t__ uint16_t ;
struct pt_section {int /*<<< orphan*/  read; int /*<<< orphan*/  unmap; int /*<<< orphan*/  mapping; struct ifix_status* status; int /*<<< orphan*/  mcount; } ;
struct ifix_status {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifix_read ; 
 int /*<<< orphan*/  ifix_unmap ; 
 int pte_internal ; 

int pt_section_map(struct pt_section *section)
{
	struct ifix_status *status;
	uint16_t mcount;

	if (!section)
		return -pte_internal;

	mcount = section->mcount++;
	if (mcount)
		return 0;

	if (section->mapping)
		return -pte_internal;

	status = section->status;
	if (!status)
		return -pte_internal;

	section->mapping = status->mapping;
	section->unmap = ifix_unmap;
	section->read = ifix_read;

	return 0;
}
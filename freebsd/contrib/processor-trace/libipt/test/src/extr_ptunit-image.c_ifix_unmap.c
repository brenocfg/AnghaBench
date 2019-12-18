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
struct pt_section {int /*<<< orphan*/ * mapping; scalar_t__ mcount; } ;

/* Variables and functions */
 int pte_internal ; 

__attribute__((used)) static int ifix_unmap(struct pt_section *section)
{
	uint16_t mcount;

	if (!section)
		return -pte_internal;

	mcount = section->mcount;
	if (!mcount)
		return -pte_internal;

	if (!section->mapping)
		return -pte_internal;

	mcount = --section->mcount;
	if (!mcount)
		section->mapping = NULL;

	return 0;
}
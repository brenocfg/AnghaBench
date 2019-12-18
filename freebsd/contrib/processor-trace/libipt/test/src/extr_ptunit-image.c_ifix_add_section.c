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
struct image_fixture {int nsecs; int /*<<< orphan*/ * mapping; int /*<<< orphan*/ * status; int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifix_init_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct image_fixture*) ; 
 int ifix_nsecs ; 
 int pte_internal ; 

__attribute__((used)) static int ifix_add_section(struct image_fixture *ifix, char *filename)
{
	int index;

	if (!ifix)
		return -pte_internal;

	index = ifix->nsecs;
	if (ifix_nsecs <= index)
		return -pte_internal;

	ifix_init_section(&ifix->section[index], filename, &ifix->status[index],
			  &ifix->mapping[index], ifix);

	ifix->nsecs += 1;
	return index;
}
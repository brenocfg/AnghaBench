#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_section {int dummy; } ;
struct TYPE_2__ {int nsecs; int /*<<< orphan*/ * laddr; struct pt_section** section; } ;
struct image_fixture {TYPE_1__ iscache; } ;

/* Variables and functions */
 int ifix_nsecs ; 
 int pte_internal ; 

__attribute__((used)) static int ifix_cache_section(struct image_fixture *ifix,
			      struct pt_section *section, uint64_t laddr)
{
	int index;

	if (!ifix)
		return -pte_internal;

	index = ifix->iscache.nsecs;
	if (ifix_nsecs <= index)
		return -pte_internal;

	ifix->iscache.section[index] = section;
	ifix->iscache.laddr[index] = laddr;

	index += 1;
	ifix->iscache.nsecs = index;

	return index;
}
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
typedef  int uint64_t ;
struct pt_section {int dummy; } ;
struct iscache_fixture {int /*<<< orphan*/  iscache; } ;

/* Variables and functions */
 int num_iterations ; 
 int pt_iscache_add_file (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int pt_iscache_lookup (int /*<<< orphan*/ *,struct pt_section**,int*,int) ; 
 int pt_section_map (struct pt_section*) ; 
 int pt_section_unmap (struct pt_section*) ; 
 int pte_internal ; 

__attribute__((used)) static int worker_add_file_map(void *arg)
{
	struct iscache_fixture *cfix;
	int it;

	cfix = arg;
	if (!cfix)
		return -pte_internal;

	for (it = 0; it < num_iterations; ++it) {
		struct pt_section *section;
		uint64_t offset, size, laddr, addr;
		int isid, errcode;

		offset = it % 7 < 4 ? 0x1000 : 0x2000;
		size = it % 5 < 3 ? 0x1000 : 0x2000;
		laddr = it % 3 < 2 ? 0x1000 : 0x2000;

		isid = pt_iscache_add_file(&cfix->iscache, "name",
					   offset, size, laddr);
		if (isid < 0)
			return isid;

		errcode = pt_iscache_lookup(&cfix->iscache, &section,
					    &addr, isid);
		if (errcode < 0)
			return errcode;

		if (addr != laddr)
			return -pte_internal;

		errcode = pt_section_map(section);
		if (errcode < 0)
			return errcode;

		errcode = pt_section_unmap(section);
		if (errcode < 0)
			return errcode;
	}

	return 0;
}
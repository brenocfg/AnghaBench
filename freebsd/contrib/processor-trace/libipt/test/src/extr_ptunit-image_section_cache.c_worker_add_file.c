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
typedef  scalar_t__ uint64_t ;
struct pt_section {scalar_t__ offset; scalar_t__ size; } ;
struct iscache_fixture {int /*<<< orphan*/  iscache; } ;

/* Variables and functions */
 int num_iterations ; 
 int num_sections ; 
 int pt_iscache_add_file (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int pt_iscache_lookup (int /*<<< orphan*/ *,struct pt_section**,scalar_t__*,int) ; 
 int pt_section_put (struct pt_section*) ; 
 int pte_bad_image ; 
 int pte_internal ; 
 int pte_noip ; 

__attribute__((used)) static int worker_add_file(void *arg)
{
	struct iscache_fixture *cfix;
	int it;

	cfix = arg;
	if (!cfix)
		return -pte_internal;

	for (it = 0; it < num_iterations; ++it) {
		uint64_t offset, size, laddr;
		int sec;

		offset = it % 7 == 0 ? 0x1000 : 0x2000;
		size = it % 5 == 0 ? 0x1000 : 0x2000;
		laddr = it % 3 == 0 ? 0x1000 : 0x2000;

		for (sec = 0; sec < num_sections; ++sec) {
			struct pt_section *section;
			uint64_t addr;
			int isid, errcode;

			isid = pt_iscache_add_file(&cfix->iscache, "name",
						   offset, size, laddr);
			if (isid < 0)
				return isid;

			errcode = pt_iscache_lookup(&cfix->iscache, &section,
						    &addr, isid);
			if (errcode < 0)
				return errcode;

			if (laddr != addr)
				return -pte_noip;

			if (section->offset != offset)
				return -pte_bad_image;

			if (section->size != size)
				return -pte_bad_image;

			errcode = pt_section_put(section);
			if (errcode < 0)
				return errcode;
		}
	}

	return 0;
}
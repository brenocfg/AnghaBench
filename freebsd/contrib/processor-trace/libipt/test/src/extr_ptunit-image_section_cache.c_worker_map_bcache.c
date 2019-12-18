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
struct pt_section {int dummy; } ;
struct iscache_fixture {struct pt_section** section; } ;

/* Variables and functions */
 int num_iterations ; 
 int num_sections ; 
 int pt_section_map (struct pt_section*) ; 
 int pt_section_request_bcache (struct pt_section*) ; 
 int pt_section_unmap (struct pt_section*) ; 
 int pte_internal ; 

__attribute__((used)) static int worker_map_bcache(void *arg)
{
	struct iscache_fixture *cfix;
	int it, sec, status;

	cfix = arg;
	if (!cfix)
		return -pte_internal;

	for (it = 0; it < num_iterations; ++it) {
		for (sec = 0; sec < num_sections; ++sec) {
			struct pt_section *section;

			section = cfix->section[sec];

			status = pt_section_map(section);
			if (status < 0)
				return status;

			if (it % 13 == 0) {
				status = pt_section_request_bcache(section);
				if (status < 0) {
					(void) pt_section_unmap(section);
					return status;
				}
			}

			status = pt_section_unmap(section);
			if (status < 0)
				return status;
		}
	}

	return 0;
}
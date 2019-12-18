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
struct iscache_fixture {int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int num_iterations ; 
 int num_sections ; 
 int pt_section_map (int /*<<< orphan*/ ) ; 
 int pt_section_unmap (int /*<<< orphan*/ ) ; 
 int pte_internal ; 

__attribute__((used)) static int worker_map(void *arg)
{
	struct iscache_fixture *cfix;
	int it, sec, status;

	cfix = arg;
	if (!cfix)
		return -pte_internal;

	for (it = 0; it < num_iterations; ++it) {
		for (sec = 0; sec < num_sections; ++sec) {

			status = pt_section_map(cfix->section[sec]);
			if (status < 0)
				return status;

			status = pt_section_unmap(cfix->section[sec]);
			if (status < 0)
				return status;
		}
	}

	return 0;
}
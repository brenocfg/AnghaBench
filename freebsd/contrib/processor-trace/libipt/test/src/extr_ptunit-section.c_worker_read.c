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
typedef  int uint8_t ;
struct section_fixture {int /*<<< orphan*/  section; } ;

/* Variables and functions */
 int num_work ; 
 int pt_section_get (int /*<<< orphan*/ ) ; 
 int pt_section_map (int /*<<< orphan*/ ) ; 
 int pt_section_put (int /*<<< orphan*/ ) ; 
 int pt_section_read (int /*<<< orphan*/ ,int*,int,int) ; 
 int pt_section_unmap (int /*<<< orphan*/ ) ; 
 int pte_internal ; 
 int pte_invalid ; 

__attribute__((used)) static int worker_read(void *arg)
{
	struct section_fixture *sfix;
	int it, errcode;

	sfix = arg;
	if (!sfix)
		return -pte_internal;

	for (it = 0; it < num_work; ++it) {
		uint8_t buffer[] = { 0xcc, 0xcc, 0xcc };
		int read;

		errcode = pt_section_get(sfix->section);
		if (errcode < 0)
			return errcode;

		errcode = pt_section_map(sfix->section);
		if (errcode < 0)
			goto out_put;

		read = pt_section_read(sfix->section, buffer, 2, 0x0ull);
		if (read < 0)
			goto out_unmap;

		errcode = -pte_invalid;
		if ((read != 2) || (buffer[0] != 0x2) || (buffer[1] != 0x4))
			goto out_unmap;

		errcode = pt_section_unmap(sfix->section);
		if (errcode < 0)
			goto out_put;

		errcode = pt_section_put(sfix->section);
		if (errcode < 0)
			return errcode;
	}

	return 0;

out_unmap:
	(void) pt_section_unmap(sfix->section);

out_put:
	(void) pt_section_put(sfix->section);
	return errcode;
}
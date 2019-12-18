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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_section {int dummy; } ;

/* Variables and functions */
 int pt_section_lock (struct pt_section*) ; 
 int pt_section_memsize_locked (struct pt_section*,int /*<<< orphan*/ *) ; 
 int pt_section_unlock (struct pt_section*) ; 

int pt_section_memsize(struct pt_section *section, uint64_t *size)
{
	int errcode, status;

	errcode = pt_section_lock(section);
	if (errcode < 0)
		return errcode;

	status = pt_section_memsize_locked(section, size);

	errcode = pt_section_unlock(section);
	if (errcode < 0)
		return errcode;

	return status;
}
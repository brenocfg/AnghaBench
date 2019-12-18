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
struct pt_section {scalar_t__ mcount; } ;

/* Variables and functions */
 int pt_section_on_map (struct pt_section*) ; 
 int pt_section_unlock (struct pt_section*) ; 
 int /*<<< orphan*/  pt_section_unmap (struct pt_section*) ; 
 int pte_internal ; 
 int pte_overflow ; 

__attribute__((used)) static int pt_sec_posix_map_success(struct pt_section *section)
{
	uint16_t mcount;
	int errcode, status;

	if (!section)
		return -pte_internal;

	mcount = section->mcount + 1;
	if (!mcount) {
		(void) pt_section_unlock(section);
		return -pte_overflow;
	}

	section->mcount = mcount;

	errcode = pt_section_unlock(section);
	if (errcode < 0)
		return errcode;

	status = pt_section_on_map(section);
	if (status < 0) {
		/* We had to release the section lock for pt_section_on_map() so
		 * @section may have meanwhile been mapped by other threads.
		 *
		 * We still want to return the error so we release our mapping.
		 * Our caller does not yet know whether pt_section_map()
		 * succeeded.
		 */
		(void) pt_section_unmap(section);
		return status;
	}

	return 0;
}
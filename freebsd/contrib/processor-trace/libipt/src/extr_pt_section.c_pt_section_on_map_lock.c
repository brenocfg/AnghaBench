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
struct pt_section {struct pt_image_section_cache* iscache; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_iscache_notify_map (struct pt_image_section_cache*,struct pt_section*) ; 
 int pt_section_lock_attach (struct pt_section*) ; 
 int pt_section_unlock_attach (struct pt_section*) ; 
 int pte_internal ; 

int pt_section_on_map_lock(struct pt_section *section)
{
	struct pt_image_section_cache *iscache;
	int errcode, status;

	if (!section)
		return -pte_internal;

	errcode = pt_section_lock_attach(section);
	if (errcode < 0)
		return errcode;

	iscache = section->iscache;
	if (!iscache)
		return pt_section_unlock_attach(section);

	/* There is a potential deadlock when @section was unmapped again and
	 * @iscache tries to map it.  This would cause this function to be
	 * re-entered while we're still holding the attach lock.
	 *
	 * This scenario is very unlikely, though, since our caller does not yet
	 * know whether pt_section_map() succeeded.
	 */
	status = pt_iscache_notify_map(iscache, section);

	errcode = pt_section_unlock_attach(section);
	if (errcode < 0)
		return errcode;

	return status;
}
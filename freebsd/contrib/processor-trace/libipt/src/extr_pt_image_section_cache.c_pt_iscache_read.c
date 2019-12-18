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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pt_section {int dummy; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ UINT16_MAX ; 
 int pt_iscache_lookup (struct pt_image_section_cache*,struct pt_section**,scalar_t__*,int) ; 
 int pt_section_map (struct pt_section*) ; 
 int pt_section_put (struct pt_section*) ; 
 int pt_section_read (struct pt_section*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int pt_section_unmap (struct pt_section*) ; 
 int pte_invalid ; 
 int pte_nomap ; 

int pt_iscache_read(struct pt_image_section_cache *iscache, uint8_t *buffer,
		    uint64_t size, int isid, uint64_t vaddr)
{
	struct pt_section *section;
	uint64_t laddr;
	int errcode, status;

	if (!iscache || !buffer || !size)
		return -pte_invalid;

	errcode = pt_iscache_lookup(iscache, &section, &laddr, isid);
	if (errcode < 0)
		return errcode;

	if (vaddr < laddr) {
		(void) pt_section_put(section);
		return -pte_nomap;
	}

	vaddr -= laddr;

	errcode = pt_section_map(section);
	if (errcode < 0) {
		(void) pt_section_put(section);
		return errcode;
	}

	/* We truncate the read if it gets too big.  The user is expected to
	 * issue further reads for the remaining part.
	 */
	if (UINT16_MAX < size)
		size = UINT16_MAX;

	status = pt_section_read(section, buffer, (uint16_t) size, vaddr);

	errcode = pt_section_unmap(section);
	if (errcode < 0) {
		(void) pt_section_put(section);
		return errcode;
	}

	errcode = pt_section_put(section);
	if (errcode < 0)
		return errcode;

	return status;
}
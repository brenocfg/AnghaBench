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
struct pt_mapped_section {struct pt_section* section; } ;
struct pt_image {struct pt_section* section; } ;

/* Variables and functions */
 int pte_internal ; 
 int pte_nomap ; 

int pt_image_validate(struct pt_image *image, struct pt_mapped_section *msec,
		      uint64_t vaddr, int isid)
{
	struct pt_section *section;

	(void) vaddr;
	(void) isid;

	if (!image || !msec)
		return -pte_internal;

	section = image->section;
	if (!section)
		return -pte_nomap;

	if (section != msec->section)
		return -pte_nomap;

	return 0;
}
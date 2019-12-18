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
struct pt_section {int (* unmap ) (struct pt_section*) ;} ;

/* Variables and functions */
 int pte_internal ; 
 int pte_nomap ; 
 int stub1 (struct pt_section*) ; 

int pt_section_unmap(struct pt_section *section)
{
	if (!section)
		return -pte_internal;

	if (!section->unmap)
		return -pte_nomap;

	return section->unmap(section);
}
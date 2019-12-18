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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pt_section {int (* read ) (struct pt_section const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int pte_internal ; 
 int pte_nomap ; 
 int stub1 (struct pt_section const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pt_section_read(const struct pt_section *section, uint8_t *buffer,
		    uint16_t size, uint64_t offset)
{
	if (!section)
		return -pte_internal;

	if (!section->read)
		return -pte_nomap;

	return section->read(section, buffer, size, offset);
}
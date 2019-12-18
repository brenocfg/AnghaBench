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
typedef  int uint16_t ;
struct pt_section {struct ifix_mapping* mapping; } ;
struct ifix_mapping {int errcode; scalar_t__ size; int /*<<< orphan*/ * content; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pte_internal ; 
 int pte_nomap ; 

__attribute__((used)) static int ifix_read(const struct pt_section *section, uint8_t *buffer,
		     uint16_t size, uint64_t offset)
{
	struct ifix_mapping *mapping;
	uint64_t begin, end;

	if (!section || !buffer)
		return -pte_internal;

	begin = offset;
	end = begin + size;

	if (end < begin)
		return -pte_nomap;

	mapping = section->mapping;
	if (!mapping)
		return -pte_nomap;

	if (mapping->errcode)
		return mapping->errcode;

	if (mapping->size <= begin)
		return -pte_nomap;

	if (mapping->size < end) {
		end = mapping->size;
		size = (uint16_t) (end - begin);
	}

	memcpy(buffer, &mapping->content[begin], size);

	return size;
}
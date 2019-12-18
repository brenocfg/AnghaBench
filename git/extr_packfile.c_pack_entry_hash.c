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
struct packed_git {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int pack_entry_hash(struct packed_git *p, off_t base_offset)
{
	unsigned int hash;

	hash = (unsigned int)(intptr_t)p + (unsigned int)base_offset;
	hash += (hash >> 8) + (hash >> 16);
	return hash;
}
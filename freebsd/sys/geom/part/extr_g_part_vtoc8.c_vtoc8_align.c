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
typedef  int uint64_t ;
struct g_part_vtoc8_table {int secpercyl; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
vtoc8_align(struct g_part_vtoc8_table *table, uint64_t *start, uint64_t *size)
{

	if (*size < table->secpercyl)
		return (EINVAL);
	if (start != NULL && (*start % table->secpercyl)) {
		*size += (*start % table->secpercyl) - table->secpercyl;
		*start -= (*start % table->secpercyl) - table->secpercyl;
	}
	if (*size % table->secpercyl)
		*size -= (*size % table->secpercyl);
	if (*size < table->secpercyl)
		return (EINVAL);
	return (0);
}
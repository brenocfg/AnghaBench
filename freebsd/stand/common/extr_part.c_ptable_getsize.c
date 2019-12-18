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
struct ptable {int sectors; int sectorsize; } ;

/* Variables and functions */
 int EOVERFLOW ; 

int
ptable_getsize(const struct ptable *table, uint64_t *sizep)
{
	uint64_t tmp = table->sectors * table->sectorsize;

	if (tmp < table->sectors)
		return (EOVERFLOW);

	if (sizep != NULL)
		*sizep = tmp;
	return (0);
}
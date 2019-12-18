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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  mon_entry ;

/* Variables and functions */
 int /*<<< orphan*/ * eallocarray (scalar_t__,int) ; 
 int /*<<< orphan*/  mon_free_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ mon_mem_increments ; 
 int /*<<< orphan*/  mru_alloc ; 
 scalar_t__ mru_incalloc ; 
 scalar_t__ mru_initalloc ; 

__attribute__((used)) static void
mon_getmoremem(void)
{
	mon_entry *chunk;
	u_int entries;

	entries = (0 == mon_mem_increments)
		      ? mru_initalloc
		      : mru_incalloc;

	if (entries) {
		chunk = eallocarray(entries, sizeof(*chunk));
		mru_alloc += entries;
		for (chunk += entries; entries; entries--)
			mon_free_entry(--chunk);

		mon_mem_increments++;
	}
}
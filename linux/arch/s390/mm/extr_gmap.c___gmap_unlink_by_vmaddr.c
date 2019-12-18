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
struct gmap {int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  host_to_guest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long PMD_SHIFT ; 
 unsigned long _SEGMENT_ENTRY_EMPTY ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __gmap_unlink_by_vmaddr(struct gmap *gmap, unsigned long vmaddr)
{
	unsigned long *entry;
	int flush = 0;

	BUG_ON(gmap_is_shadow(gmap));
	spin_lock(&gmap->guest_table_lock);
	entry = radix_tree_delete(&gmap->host_to_guest, vmaddr >> PMD_SHIFT);
	if (entry) {
		flush = (*entry != _SEGMENT_ENTRY_EMPTY);
		*entry = _SEGMENT_ENTRY_EMPTY;
	}
	spin_unlock(&gmap->guest_table_lock);
	return flush;
}
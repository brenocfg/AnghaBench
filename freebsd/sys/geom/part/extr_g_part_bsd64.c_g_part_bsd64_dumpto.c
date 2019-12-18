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
struct g_part_table {int dummy; } ;
struct g_part_entry {int dummy; } ;
struct g_part_bsd64_entry {scalar_t__ fstype; int /*<<< orphan*/  type_uuid; } ;

/* Variables and functions */
 scalar_t__ EQUUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FS_SWAP ; 
 int /*<<< orphan*/  bsd64_uuid_dfbsd_swap ; 
 int /*<<< orphan*/  bsd64_uuid_freebsd_swap ; 

__attribute__((used)) static int
g_part_bsd64_dumpto(struct g_part_table *table, struct g_part_entry *baseentry)
{
	struct g_part_bsd64_entry *entry;

	/* Allow dumping to a swap partition. */
	entry = (struct g_part_bsd64_entry *)baseentry;
	if (entry->fstype == FS_SWAP ||
	    EQUUID(&entry->type_uuid, &bsd64_uuid_dfbsd_swap) ||
	    EQUUID(&entry->type_uuid, &bsd64_uuid_freebsd_swap))
		return (1);
	return (0);
}
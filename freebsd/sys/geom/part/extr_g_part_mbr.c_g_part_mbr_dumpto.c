#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_part_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ dp_typ; } ;
struct g_part_mbr_entry {TYPE_1__ ent; } ;
struct g_part_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DOSPTYP_386BSD ; 
 scalar_t__ DOSPTYP_LINSWP ; 

__attribute__((used)) static int
g_part_mbr_dumpto(struct g_part_table *table, struct g_part_entry *baseentry)
{
	struct g_part_mbr_entry *entry;

	/* Allow dumping to a FreeBSD partition or Linux swap partition only. */
	entry = (struct g_part_mbr_entry *)baseentry;
	return ((entry->ent.dp_typ == DOSPTYP_386BSD ||
	    entry->ent.dp_typ == DOSPTYP_LINSWP) ? 1 : 0);
}
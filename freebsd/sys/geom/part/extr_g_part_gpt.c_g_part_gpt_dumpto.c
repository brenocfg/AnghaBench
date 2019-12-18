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
struct TYPE_2__ {int /*<<< orphan*/  ent_type; } ;
struct g_part_gpt_entry {TYPE_1__ ent; } ;
struct g_part_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ EQUUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpt_uuid_dfbsd_swap ; 
 int /*<<< orphan*/  gpt_uuid_freebsd_swap ; 
 int /*<<< orphan*/  gpt_uuid_linux_swap ; 

__attribute__((used)) static int
g_part_gpt_dumpto(struct g_part_table *table, struct g_part_entry *baseentry)
{
	struct g_part_gpt_entry *entry;

	entry = (struct g_part_gpt_entry *)baseentry;
	return ((EQUUID(&entry->ent.ent_type, &gpt_uuid_freebsd_swap) ||
	    EQUUID(&entry->ent.ent_type, &gpt_uuid_linux_swap) ||
	    EQUUID(&entry->ent.ent_type, &gpt_uuid_dfbsd_swap)) ? 1 : 0);
}
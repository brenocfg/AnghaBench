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
struct g_part_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ent_type; } ;
struct g_part_apm_entry {TYPE_1__ ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_SWAP ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_apm_dumpto(struct g_part_table *table, struct g_part_entry *baseentry)
{
	struct g_part_apm_entry *entry;

	entry = (struct g_part_apm_entry *)baseentry;
	return ((!strcmp(entry->ent.ent_type, APM_ENT_TYPE_FREEBSD_SWAP))
	    ? 1 : 0);
}
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
struct g_part_entry {int /*<<< orphan*/  gpe_index; } ;

/* Variables and functions */
 scalar_t__ EQUUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpt_uuid_freebsd ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
g_part_gpt_name(struct g_part_table *table, struct g_part_entry *baseentry,
    char *buf, size_t bufsz)
{
	struct g_part_gpt_entry *entry;
	char c;

	entry = (struct g_part_gpt_entry *)baseentry;
	c = (EQUUID(&entry->ent.ent_type, &gpt_uuid_freebsd)) ? 's' : 'p';
	snprintf(buf, bufsz, "%c%d", c, baseentry->gpe_index);
	return (buf);
}
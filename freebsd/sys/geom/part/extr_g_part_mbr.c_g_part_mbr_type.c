#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_part_table {int dummy; } ;
struct TYPE_4__ {scalar_t__ dp_typ; } ;
struct g_part_mbr_entry {TYPE_1__ ent; } ;
struct g_part_entry {int dummy; } ;
struct TYPE_5__ {scalar_t__ typ; int /*<<< orphan*/  alias; } ;

/* Variables and functions */
 char const* g_part_alias_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* mbr_alias_match ; 
 int nitems (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static const char *
g_part_mbr_type(struct g_part_table *basetable, struct g_part_entry *baseentry,
    char *buf, size_t bufsz)
{
	struct g_part_mbr_entry *entry;
	int i;

	entry = (struct g_part_mbr_entry *)baseentry;
	for (i = 0; i < nitems(mbr_alias_match); i++) {
		if (mbr_alias_match[i].typ == entry->ent.dp_typ)
			return (g_part_alias_name(mbr_alias_match[i].alias));
	}
	snprintf(buf, bufsz, "!%d", entry->ent.dp_typ);
	return (buf);
}
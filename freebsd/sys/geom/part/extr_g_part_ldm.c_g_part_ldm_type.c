#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_part_table {int dummy; } ;
struct g_part_ldm_entry {scalar_t__ type; } ;
struct g_part_entry {int dummy; } ;
struct TYPE_3__ {scalar_t__ typ; int /*<<< orphan*/  alias; } ;

/* Variables and functions */
 char const* g_part_alias_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldm_alias_match ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,scalar_t__) ; 

__attribute__((used)) static const char *
g_part_ldm_type(struct g_part_table *basetable, struct g_part_entry *baseentry,
    char *buf, size_t bufsz)
{
	struct g_part_ldm_entry *entry;
	int i;

	entry = (struct g_part_ldm_entry *)baseentry;
	for (i = 0; i < nitems(ldm_alias_match); i++) {
		if (ldm_alias_match[i].typ == entry->type)
			return (g_part_alias_name(ldm_alias_match[i].alias));
	}
	snprintf(buf, bufsz, "!%d", entry->type);
	return (buf);
}
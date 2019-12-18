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
struct sbuf {int dummy; } ;
struct g_part_table {int dummy; } ;
struct g_part_ldm_entry {int /*<<< orphan*/  type; } ;
struct g_part_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 

__attribute__((used)) static void
g_part_ldm_dumpconf(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct sbuf *sb, const char *indent)
{
	struct g_part_ldm_entry *entry;

	entry = (struct g_part_ldm_entry *)baseentry;
	if (indent == NULL) {
		/* conftxt: libdisk compatibility */
		sbuf_printf(sb, " xs LDM xt %u", entry->type);
	} else if (entry != NULL) {
		/* confxml: partition entry information */
		sbuf_printf(sb, "%s<rawtype>%u</rawtype>\n", indent,
		    entry->type);
	} else {
		/* confxml: scheme information */
	}
}
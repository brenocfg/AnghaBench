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
typedef  int /*<<< orphan*/  uintmax_t ;
struct sbuf {int dummy; } ;
struct g_part_table {int dummy; } ;
struct g_part_entry {int dummy; } ;
struct g_part_bsd64_table {int /*<<< orphan*/  d_packname; int /*<<< orphan*/  d_stor_uuid; scalar_t__ d_abase; scalar_t__ d_bbase; } ;
struct g_part_bsd64_entry {char const* fstype; int /*<<< orphan*/  stor_uuid; int /*<<< orphan*/  type_uuid; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EQUUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsd64_uuid_unused ; 
 int /*<<< orphan*/  g_conf_cat_escaped (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  sbuf_printf_uuid (struct sbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_part_bsd64_dumpconf(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct sbuf *sb, const char *indent)
{
	struct g_part_bsd64_table *table;
	struct g_part_bsd64_entry *entry;
	char buf[sizeof(table->d_packname)];

	entry = (struct g_part_bsd64_entry *)baseentry;
	if (indent == NULL) {
		/* conftxt: libdisk compatibility */
		sbuf_printf(sb, " xs BSD64 xt %u", entry->fstype);
	} else if (entry != NULL) {
		/* confxml: partition entry information */
		sbuf_printf(sb, "%s<rawtype>%u</rawtype>\n", indent,
		    entry->fstype);
		if (!EQUUID(&bsd64_uuid_unused, &entry->type_uuid)) {
			sbuf_printf(sb, "%s<type_uuid>", indent);
			sbuf_printf_uuid(sb, &entry->type_uuid);
			sbuf_cat(sb, "</type_uuid>\n");
		}
		sbuf_printf(sb, "%s<stor_uuid>", indent);
		sbuf_printf_uuid(sb, &entry->stor_uuid);
		sbuf_cat(sb, "</stor_uuid>\n");
	} else {
		/* confxml: scheme information */
		table = (struct g_part_bsd64_table *)basetable;
		sbuf_printf(sb, "%s<bootbase>%ju</bootbase>\n", indent,
		    (uintmax_t)table->d_bbase);
		if (table->d_abase)
			sbuf_printf(sb, "%s<backupbase>%ju</backupbase>\n",
			    indent, (uintmax_t)table->d_abase);
		sbuf_printf(sb, "%s<stor_uuid>", indent);
		sbuf_printf_uuid(sb, &table->d_stor_uuid);
		sbuf_cat(sb, "</stor_uuid>\n");
		sbuf_printf(sb, "%s<label>", indent);
		strncpy(buf, table->d_packname, sizeof(buf) - 1);
		buf[sizeof(buf) - 1] = '\0';
		g_conf_cat_escaped(sb, buf);
		sbuf_cat(sb, "</label>\n");
	}
}
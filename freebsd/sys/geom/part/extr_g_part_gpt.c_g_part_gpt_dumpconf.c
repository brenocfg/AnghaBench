#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
struct g_part_table {int dummy; } ;
struct TYPE_4__ {scalar_t__ gpe_start; scalar_t__ gpe_end; int /*<<< orphan*/  gpe_index; } ;
struct TYPE_3__ {int ent_attr; int /*<<< orphan*/  ent_uuid; int /*<<< orphan*/  ent_type; int /*<<< orphan*/  ent_name; } ;
struct g_part_gpt_entry {TYPE_2__ base; TYPE_1__ ent; } ;
struct g_part_entry {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int GPT_ENT_ATTR_BOOTFAILED ; 
 int GPT_ENT_ATTR_BOOTME ; 
 int GPT_ENT_ATTR_BOOTONCE ; 
 int /*<<< orphan*/  g_gpt_printf_utf16 (struct sbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  sbuf_printf_uuid (struct sbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_part_gpt_dumpconf(struct g_part_table *table, struct g_part_entry *baseentry,
    struct sbuf *sb, const char *indent)
{
	struct g_part_gpt_entry *entry;

	entry = (struct g_part_gpt_entry *)baseentry;
	if (indent == NULL) {
		/* conftxt: libdisk compatibility */
		sbuf_cat(sb, " xs GPT xt ");
		sbuf_printf_uuid(sb, &entry->ent.ent_type);
	} else if (entry != NULL) {
		/* confxml: partition entry information */
		sbuf_printf(sb, "%s<label>", indent);
		g_gpt_printf_utf16(sb, entry->ent.ent_name,
		    sizeof(entry->ent.ent_name) >> 1);
		sbuf_cat(sb, "</label>\n");
		if (entry->ent.ent_attr & GPT_ENT_ATTR_BOOTME)
			sbuf_printf(sb, "%s<attrib>bootme</attrib>\n", indent);
		if (entry->ent.ent_attr & GPT_ENT_ATTR_BOOTONCE) {
			sbuf_printf(sb, "%s<attrib>bootonce</attrib>\n",
			    indent);
		}
		if (entry->ent.ent_attr & GPT_ENT_ATTR_BOOTFAILED) {
			sbuf_printf(sb, "%s<attrib>bootfailed</attrib>\n",
			    indent);
		}
		sbuf_printf(sb, "%s<rawtype>", indent);
		sbuf_printf_uuid(sb, &entry->ent.ent_type);
		sbuf_cat(sb, "</rawtype>\n");
		sbuf_printf(sb, "%s<rawuuid>", indent);
		sbuf_printf_uuid(sb, &entry->ent.ent_uuid);
		sbuf_cat(sb, "</rawuuid>\n");
		sbuf_printf(sb, "%s<efimedia>", indent);
		sbuf_printf(sb, "HD(%d,GPT,", entry->base.gpe_index);
		sbuf_printf_uuid(sb, &entry->ent.ent_uuid);
		sbuf_printf(sb, ",%#jx,%#jx)", (intmax_t)entry->base.gpe_start,
		    (intmax_t)(entry->base.gpe_end - entry->base.gpe_start + 1));
		sbuf_cat(sb, "</efimedia>\n");
	} else {
		/* confxml: scheme information */
	}
}
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
struct g_part_parms {int gpp_parms; int /*<<< orphan*/  gpp_label; int /*<<< orphan*/  gpp_type; } ;
struct g_part_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ent_name; int /*<<< orphan*/  ent_type; } ;
struct g_part_apm_entry {TYPE_1__ ent; } ;

/* Variables and functions */
 int EINVAL ; 
 int G_PART_PARM_LABEL ; 
 int G_PART_PARM_TYPE ; 
 int apm_parse_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
g_part_apm_modify(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct g_part_parms *gpp)
{
	struct g_part_apm_entry *entry;
	int error;

	entry = (struct g_part_apm_entry *)baseentry;
	if (gpp->gpp_parms & G_PART_PARM_LABEL) {
		if (strlen(gpp->gpp_label) > sizeof(entry->ent.ent_name))
			return (EINVAL);
	}
	if (gpp->gpp_parms & G_PART_PARM_TYPE) {
		error = apm_parse_type(gpp->gpp_type, entry->ent.ent_type,
		    sizeof(entry->ent.ent_type));
		if (error)
			return (error);
	}
	if (gpp->gpp_parms & G_PART_PARM_LABEL) {
		strncpy(entry->ent.ent_name, gpp->gpp_label,
		    sizeof(entry->ent.ent_name));
	}
	return (0);
}
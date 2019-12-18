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
struct g_part_parms {int gpp_parms; int /*<<< orphan*/  gpp_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dp_typ; } ;
struct g_part_mbr_entry {TYPE_1__ ent; } ;
struct g_part_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int G_PART_PARM_LABEL ; 
 int G_PART_PARM_TYPE ; 
 int mbr_parse_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_mbr_modify(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct g_part_parms *gpp)
{
	struct g_part_mbr_entry *entry;

	if (gpp->gpp_parms & G_PART_PARM_LABEL)
		return (EINVAL);

	entry = (struct g_part_mbr_entry *)baseentry;
	if (gpp->gpp_parms & G_PART_PARM_TYPE)
		return (mbr_parse_type(gpp->gpp_type, &entry->ent.dp_typ));
	return (0);
}
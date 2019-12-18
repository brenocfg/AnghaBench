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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {TYPE_2__* part; } ;
struct g_part_vtoc8_table {TYPE_1__ vtoc; } ;
struct g_part_table {int dummy; } ;
struct g_part_parms {int gpp_parms; int /*<<< orphan*/  gpp_type; } ;
struct g_part_entry {int gpe_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int EINVAL ; 
 int G_PART_PARM_LABEL ; 
 int G_PART_PARM_TYPE ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vtoc8_parse_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_vtoc8_modify(struct g_part_table *basetable,
    struct g_part_entry *entry, struct g_part_parms *gpp)
{
	struct g_part_vtoc8_table *table;
	int error;
	uint16_t tag;

	if (gpp->gpp_parms & G_PART_PARM_LABEL)
		return (EINVAL);

	table = (struct g_part_vtoc8_table *)basetable;
	if (gpp->gpp_parms & G_PART_PARM_TYPE) {
		error = vtoc8_parse_type(gpp->gpp_type, &tag);
		if (error)
			return(error);

		be16enc(&table->vtoc.part[entry->gpe_index - 1].tag, tag);
	}
	return (0);
}
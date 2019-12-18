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
struct g_part_table {int dummy; } ;
struct g_part_parms {int gpp_parms; int /*<<< orphan*/  gpp_type; } ;
struct g_part_entry {int dummy; } ;
struct g_part_bsd64_entry {int /*<<< orphan*/  stor_uuid; } ;

/* Variables and functions */
 int EINVAL ; 
 int G_PART_PARM_LABEL ; 
 scalar_t__ bsd64_parse_type (int /*<<< orphan*/ ,struct g_part_bsd64_entry*) ; 
 int /*<<< orphan*/  kern_uuidgen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
g_part_bsd64_add(struct g_part_table *basetable, struct g_part_entry *baseentry,
    struct g_part_parms *gpp)
{
	struct g_part_bsd64_entry *entry;

	if (gpp->gpp_parms & G_PART_PARM_LABEL)
		return (EINVAL);

	entry = (struct g_part_bsd64_entry *)baseentry;
	if (bsd64_parse_type(gpp->gpp_type, entry) != 0)
		return (EINVAL);
	kern_uuidgen(&entry->stor_uuid, 1);
	return (0);
}
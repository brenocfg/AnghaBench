#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dsk {int dummy; } ;
struct TYPE_6__ {int ent_attr; } ;
struct TYPE_5__ {int ent_attr; } ;

/* Variables and functions */
 int GPT_ENT_ATTR_BOOTFAILED ; 
 int GPT_ENT_ATTR_BOOTONCE ; 
 size_t curent ; 
 TYPE_4__* gpttable ; 
 int /*<<< orphan*/  gptupdate (char*,struct dsk*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hdr_backup ; 
 scalar_t__ hdr_backup_lba ; 
 int /*<<< orphan*/  hdr_primary ; 
 scalar_t__ hdr_primary_lba ; 
 TYPE_1__* table_backup ; 
 TYPE_1__* table_primary ; 

void
gptbootfailed(struct dsk *dskp)
{

	if (!(gpttable[curent].ent_attr & GPT_ENT_ATTR_BOOTONCE))
		return;

	if (hdr_primary_lba > 0) {
		table_primary[curent].ent_attr &= ~GPT_ENT_ATTR_BOOTONCE;
		table_primary[curent].ent_attr |= GPT_ENT_ATTR_BOOTFAILED;
		gptupdate("primary", dskp, &hdr_primary, table_primary);
	}
	if (hdr_backup_lba > 0) {
		table_backup[curent].ent_attr &= ~GPT_ENT_ATTR_BOOTONCE;
		table_backup[curent].ent_attr |= GPT_ENT_ATTR_BOOTFAILED;
		gptupdate("backup", dskp, &hdr_backup, table_backup);
	}
}
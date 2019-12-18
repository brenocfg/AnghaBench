#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_table {TYPE_1__* gpt_gp; } ;
struct g_part_gpt_table {int* mbr; scalar_t__ bootcamp; } ;
struct TYPE_5__ {int ent_attr; } ;
struct g_part_gpt_entry {TYPE_2__ ent; } ;
struct g_part_entry {int gpe_index; int gpe_modified; int /*<<< orphan*/  gpe_created; } ;
struct TYPE_6__ {struct g_provider* provider; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int GPT_ENT_ATTR_BOOTFAILED ; 
 int GPT_ENT_ATTR_BOOTME ; 
 int GPT_ENT_ATTR_BOOTONCE ; 
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int NDOSPART ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  gpt_write_mbr_entry (int*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
g_part_gpt_setunset(struct g_part_table *basetable,
    struct g_part_entry *baseentry, const char *attrib, unsigned int set)
{
	struct g_part_gpt_entry *entry;
	struct g_part_gpt_table *table;
	struct g_provider *pp;
	uint8_t *p;
	uint64_t attr;
	int i;

	table = (struct g_part_gpt_table *)basetable;
	entry = (struct g_part_gpt_entry *)baseentry;

	if (strcasecmp(attrib, "active") == 0) {
		if (table->bootcamp) {
			/* The active flag must be set on a valid entry. */
			if (entry == NULL)
				return (ENXIO);
			if (baseentry->gpe_index > NDOSPART)
				return (EINVAL);
			for (i = 0; i < NDOSPART; i++) {
				p = &table->mbr[DOSPARTOFF + i * DOSPARTSIZE];
				p[0] = (i == baseentry->gpe_index - 1)
				    ? ((set) ? 0x80 : 0) : 0;
			}
		} else {
			/* The PMBR is marked as active without an entry. */
			if (entry != NULL)
				return (ENXIO);
			for (i = 0; i < NDOSPART; i++) {
				p = &table->mbr[DOSPARTOFF + i * DOSPARTSIZE];
				p[0] = (p[4] == 0xee) ? ((set) ? 0x80 : 0) : 0;
			}
		}
		return (0);
	} else if (strcasecmp(attrib, "lenovofix") == 0) {
		/*
		 * Write the 0xee GPT entry to slot #1 (2nd slot) in the pMBR.
		 * This workaround allows Lenovo X220, T420, T520, etc to boot
		 * from GPT Partitions in BIOS mode.
		 */

		if (entry != NULL)
			return (ENXIO);

		pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
		bzero(table->mbr + DOSPARTOFF, DOSPARTSIZE * NDOSPART);
		gpt_write_mbr_entry(table->mbr, ((set) ? 1 : 0), 0xee, 1,
		    MIN(pp->mediasize / pp->sectorsize - 1, UINT32_MAX));
		return (0);
	}

	if (entry == NULL)
		return (ENODEV);

	attr = 0;
	if (strcasecmp(attrib, "bootme") == 0) {
		attr |= GPT_ENT_ATTR_BOOTME;
	} else if (strcasecmp(attrib, "bootonce") == 0) {
		attr |= GPT_ENT_ATTR_BOOTONCE;
		if (set)
			attr |= GPT_ENT_ATTR_BOOTME;
	} else if (strcasecmp(attrib, "bootfailed") == 0) {
		/*
		 * It should only be possible to unset BOOTFAILED, but it might
		 * be useful for test purposes to also be able to set it.
		 */
		attr |= GPT_ENT_ATTR_BOOTFAILED;
	}
	if (attr == 0)
		return (EINVAL);

	if (set)
		attr = entry->ent.ent_attr | attr;
	else
		attr = entry->ent.ent_attr & ~attr;
	if (attr != entry->ent.ent_attr) {
		entry->ent.ent_attr = attr;
		if (!baseentry->gpe_created)
			baseentry->gpe_modified = 1;
	}
	return (0);
}
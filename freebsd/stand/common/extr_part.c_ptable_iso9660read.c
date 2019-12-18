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
typedef  int /*<<< orphan*/  uint8_t ;
struct ptable {int sectorsize; int /*<<< orphan*/  type; int /*<<< orphan*/  entries; int /*<<< orphan*/  sectors; } ;
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  type; int /*<<< orphan*/  end; scalar_t__ start; } ;
struct pentry {TYPE_1__ part; } ;
struct iso_primary_descriptor {int /*<<< orphan*/  id; } ;
typedef  scalar_t__ (* diskread_t ) (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  ISO_STANDARD_ID ; 
 int /*<<< orphan*/  PART_ISO9660 ; 
 int /*<<< orphan*/  PTABLE_ISO9660 ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pentry*,struct pentry*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdb2devb (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  ptable_close (struct ptable*) ; 

__attribute__((used)) static struct ptable *
ptable_iso9660read(struct ptable *table, void *dev, diskread_t dread)
{
	uint8_t *buf;
	struct iso_primary_descriptor *vd;
	struct pentry *entry;

	buf = malloc(table->sectorsize);
	if (buf == NULL)
		return (table);
		
	if (dread(dev, buf, 1, cdb2devb(16)) != 0) {
		DPRINTF("read failed");
		ptable_close(table);
		table = NULL;
		goto out;
	}
	vd = (struct iso_primary_descriptor *)buf;
	if (bcmp(vd->id, ISO_STANDARD_ID, sizeof vd->id) != 0)
		goto out;

	entry = malloc(sizeof(*entry));
	if (entry == NULL)
		goto out;
	entry->part.start = 0;
	entry->part.end = table->sectors;
	entry->part.type = PART_ISO9660;
	entry->part.index = 0;
	STAILQ_INSERT_TAIL(&table->entries, entry, entry);

	table->type = PTABLE_ISO9660;

out:
	free(buf);
	return (table);
}
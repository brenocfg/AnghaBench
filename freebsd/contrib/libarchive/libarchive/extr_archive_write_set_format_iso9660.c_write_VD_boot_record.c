#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* catalog; } ;
struct iso9660 {TYPE_4__ el_torito; } ;
struct archive_write {struct iso9660* format_data; } ;
struct TYPE_7__ {TYPE_2__* file; } ;
struct TYPE_5__ {int /*<<< orphan*/  location; } ;
struct TYPE_6__ {TYPE_1__ content; } ;

/* Variables and functions */
 int LOGICAL_BLOCK_SIZE ; 
 int /*<<< orphan*/  VDT_BOOT_RECORD ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  set_VD_bp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_num_731 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unused_field_bp (unsigned char*,int,int) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int) ; 

__attribute__((used)) static int
write_VD_boot_record(struct archive_write *a)
{
	struct iso9660 *iso9660;
	unsigned char *bp;

	iso9660 = a->format_data;
	bp = wb_buffptr(a) -1;
	/* Volume Descriptor Type */
	set_VD_bp(bp, VDT_BOOT_RECORD, 1);
	/* Boot System Identifier */
	memcpy(bp+8, "EL TORITO SPECIFICATION", 23);
	set_unused_field_bp(bp, 8+23, 39);
	/* Unused */
	set_unused_field_bp(bp, 40, 71);
	/* Absolute pointer to first sector of Boot Catalog */
	set_num_731(bp+72,
	    iso9660->el_torito.catalog->file->content.location);
	/* Unused */
	set_unused_field_bp(bp, 76, LOGICAL_BLOCK_SIZE);

	return (wb_consume(a, LOGICAL_BLOCK_SIZE));
}
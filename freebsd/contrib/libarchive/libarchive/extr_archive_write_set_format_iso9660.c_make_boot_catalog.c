#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  s; } ;
struct TYPE_9__ {unsigned char platform_id; unsigned char media_type; int boot_load_seg; unsigned char system_type; int boot_load_size; TYPE_3__* boot; TYPE_5__ id; } ;
struct iso9660 {TYPE_4__ el_torito; } ;
struct archive_write {struct iso9660* format_data; } ;
struct TYPE_8__ {TYPE_2__* file; } ;
struct TYPE_6__ {int /*<<< orphan*/  location; } ;
struct TYPE_7__ {TYPE_1__ content; } ;

/* Variables and functions */
 unsigned char BOOT_MEDIA_NO_EMULATION ; 
 int LOGICAL_BLOCK_SIZE ; 
 scalar_t__ archive_le16dec (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_strlen (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_num_721 (unsigned char*,int) ; 
 int /*<<< orphan*/  set_num_731 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int) ; 

__attribute__((used)) static int
make_boot_catalog(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;
	unsigned char *block;
	unsigned char *p;
	uint16_t sum, *wp;

	block = wb_buffptr(a);
	memset(block, 0, LOGICAL_BLOCK_SIZE);
	p = block;
	/*
	 * Validation Entry
	 */
	/* Header ID */
	p[0] = 1;
	/* Platform ID */
	p[1] = iso9660->el_torito.platform_id;
	/* Reserved */
	p[2] = p[3] = 0;
	/* ID */
	if (archive_strlen(&(iso9660->el_torito.id)) > 0)
		strncpy((char *)p+4, iso9660->el_torito.id.s, 23);
	p[27] = 0;
	/* Checksum */
	p[28] = p[29] = 0;
	/* Key */
	p[30] = 0x55;
	p[31] = 0xAA;

	sum = 0;
	wp = (uint16_t *)block;
	while (wp < (uint16_t *)&block[32])
		sum += archive_le16dec(wp++);
	set_num_721(&block[28], (~sum) + 1);

	/*
	 * Initial/Default Entry
	 */
	p = &block[32];
	/* Boot Indicator */
	p[0] = 0x88;
	/* Boot media type */
	p[1] = iso9660->el_torito.media_type;
	/* Load Segment */
	if (iso9660->el_torito.media_type == BOOT_MEDIA_NO_EMULATION)
		set_num_721(&p[2], iso9660->el_torito.boot_load_seg);
	else
		set_num_721(&p[2], 0);
	/* System Type */
	p[4] = iso9660->el_torito.system_type;
	/* Unused */
	p[5] = 0;
	/* Sector Count */
	if (iso9660->el_torito.media_type == BOOT_MEDIA_NO_EMULATION)
		set_num_721(&p[6], iso9660->el_torito.boot_load_size);
	else
		set_num_721(&p[6], 1);
	/* Load RBA */
	set_num_731(&p[8],
	    iso9660->el_torito.boot->file->content.location);
	/* Unused */
	memset(&p[12], 0, 20);

	return (wb_consume(a, LOGICAL_BLOCK_SIZE));
}
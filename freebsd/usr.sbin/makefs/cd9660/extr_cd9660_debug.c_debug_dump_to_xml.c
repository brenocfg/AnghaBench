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
typedef  int /*<<< orphan*/  u_char ;
struct iso_primary_descriptor {scalar_t__ type_m_path_table; scalar_t__ path_table_size; scalar_t__ type_l_path_table; } ;
struct _boot_volume_descriptor {scalar_t__ type_m_path_table; scalar_t__ path_table_size; scalar_t__ type_l_path_table; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CD9660_SECTOR_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  debug_dump_to_xml_path_table (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  debug_dump_to_xml_volume_descriptor (unsigned char*,int) ; 
 int debug_get_encoded_number (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int fseeko (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct iso_primary_descriptor*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
debug_dump_to_xml(FILE *fd)
{
	unsigned char buf[CD9660_SECTOR_SIZE];
	off_t sector;
	int t, t2;
	struct iso_primary_descriptor primaryVD;
	struct _boot_volume_descriptor bootVD;

	printf("<cd9660dump>\n");

	/* Display Volume Descriptors */
	sector = 16;
	do {
		if (fseeko(fd, CD9660_SECTOR_SIZE * sector, SEEK_SET) == -1)
			err(1, "fseeko");
		fread(buf, 1, CD9660_SECTOR_SIZE, fd);
		t = (int)((unsigned char)buf[0]);
		switch (t) {
		case 0:
			memcpy(&bootVD, buf, CD9660_SECTOR_SIZE);
			break;
		case 1:
			memcpy(&primaryVD, buf, CD9660_SECTOR_SIZE);
			break;
		}
		debug_dump_to_xml_volume_descriptor(buf, sector);
		sector++;
	} while (t != 255);

	t = debug_get_encoded_number((u_char *)primaryVD.type_l_path_table,
	    731);
	t2 = debug_get_encoded_number((u_char *)primaryVD.path_table_size, 733);
	printf("Path table 1 located at sector %i and is %i bytes long\n",
	    t,t2);
	debug_dump_to_xml_path_table(fd, t, t2, 721);

	t = debug_get_encoded_number((u_char *)primaryVD.type_m_path_table,
	    731);
	debug_dump_to_xml_path_table(fd, t, t2, 722);

	printf("</cd9660dump>\n");
}
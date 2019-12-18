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
struct sch2_header {int magic; int cp_type; int version; int ram_addr; int image_len; int image_crc32; int start_addr; int rootfs_addr; int rootfs_len; int rootfs_crc32; int header_crc32; int header_length; int cmd_line_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

void print_sch2_header(struct sch2_header *printed_header)
{
	printf("\tmagic: 0x%04X\n"
	       "\tcp_type: 0x%02X\n"
	       "\tversion: 0x%02X\n"
	       "\tram_addr: 0x%08X\n"
	       "\timage_len: 0x%08X\n"
	       "\timage_crc32: 0x%08X\n"
	       "\tstart_addr: 0x%08X\n"
	       "\trootfs_addr: 0x%08X\n"
	       "\trootfs_len: 0x%08X\n"
	       "\trootfs_crc32: 0x%08X\n"
	       "\theader_crc32: 0x%08X\n"
	       "\theader_length: 0x%04X\n"
	       "\tcmd_line_length: 0x%04X\n",
	       printed_header->magic,
	       printed_header->cp_type,
	       printed_header->version,
	       printed_header->ram_addr,
	       printed_header->image_len,
	       printed_header->image_crc32,
	       printed_header->start_addr,
	       printed_header->rootfs_addr,
	       printed_header->rootfs_len,
	       printed_header->rootfs_crc32,
	       printed_header->header_crc32,
	       printed_header->header_length, printed_header->cmd_line_length);
}
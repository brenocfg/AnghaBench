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
struct iso_directory_record {char* length; char* ext_attr_length; char* flags; char* file_unit_size; char* interleave; char* volume_sequence_number; char* name_len; scalar_t__ name; scalar_t__ size; scalar_t__ extent; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_dump_integer (char*,char*,int) ; 
 int /*<<< orphan*/  debug_dump_to_xml_padded_hex_output (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_get_encoded_number (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
debug_dump_directory_record_9_1(unsigned char* buf)
{
	printf("<directoryrecord>\n");
	debug_dump_integer("length",
	    ((struct iso_directory_record*) buf)->length, 711);
	debug_dump_integer("ext_attr_length",
	    ((struct iso_directory_record*) buf)->ext_attr_length,711);
	debug_dump_integer("extent",
	    (char *)((struct iso_directory_record*) buf)->extent, 733);
	debug_dump_integer("size",
	    (char *)((struct iso_directory_record*) buf)->size, 733);
	debug_dump_integer("flags",
	    ((struct iso_directory_record*) buf)->flags, 711);
	debug_dump_integer("file_unit_size",
	    ((struct iso_directory_record*) buf)->file_unit_size,711);
	debug_dump_integer("interleave",
	    ((struct iso_directory_record*) buf)->interleave, 711);
	debug_dump_integer("volume_sequence_number",
	    ((struct iso_directory_record*) buf)->volume_sequence_number,
	    723);
	debug_dump_integer("name_len",
	    ((struct iso_directory_record*) buf)->name_len, 711);
	debug_dump_to_xml_padded_hex_output("name",
	    (u_char *)((struct iso_directory_record*) buf)->name,
		debug_get_encoded_number((u_char *)
		    ((struct iso_directory_record*) buf)->length, 711));
	printf("</directoryrecord>\n");
}
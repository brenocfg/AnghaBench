#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* length; int* extended_attribute_length; int /*<<< orphan*/  name; int /*<<< orphan*/  parent_number; } ;
typedef  TYPE_1__ path_table_entry ;

/* Variables and functions */
 int /*<<< orphan*/  debug_dump_to_xml_padded_hex_output (char*,int /*<<< orphan*/ ,int) ; 
 int debug_get_encoded_number (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
debug_dump_to_xml_ptentry(path_table_entry *pttemp, int num, int mode)
{
	printf("<ptentry num=\"%i\">\n" ,num);
	printf("<length>%i</length>\n", pttemp->length[0]);
	printf("<extended_attribute_length>%i</extended_attribute_length>\n",
	    pttemp->extended_attribute_length[0]);
	printf("<parent_number>%i</parent_number>\n",
	    debug_get_encoded_number(pttemp->parent_number,mode));
	debug_dump_to_xml_padded_hex_output("name",
	    pttemp->name, pttemp->length[0]);
	printf("</ptentry>\n");
}
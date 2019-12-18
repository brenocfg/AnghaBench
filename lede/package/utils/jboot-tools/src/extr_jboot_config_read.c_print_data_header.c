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
typedef  size_t uint16_t ;
struct data_header {int id; int type; int unknown; int length; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_data_header(struct data_header *printed_header)
{
	printf("id: 0x%02X "
	       "type: 0x%02X "
	       "unknown: 0x%04X "
	       "length: 0x%04X\n"
	       "data: ",
	       printed_header->id,
	       printed_header->type,
	       printed_header->unknown, printed_header->length);

	for (uint16_t i = 0; i < printed_header->length; i++)
		printf("%02X ", printed_header->data[i]);

	printf("\n");

}
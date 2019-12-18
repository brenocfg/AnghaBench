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
typedef  int uint16_t ;
struct nvme_opcode_string {int opc; char const* str; } ;

/* Variables and functions */
 struct nvme_opcode_string* admin_opcode ; 

__attribute__((used)) static const char *
get_admin_opcode_string(uint16_t opc)
{
	struct nvme_opcode_string *entry;

	entry = admin_opcode;

	while (entry->opc != 0xFFFF) {
		if (entry->opc == opc)
			return (entry->str);
		entry++;
	}
	return (entry->str);
}
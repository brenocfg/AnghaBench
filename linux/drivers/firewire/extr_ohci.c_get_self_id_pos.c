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
typedef  int u32 ;
struct fw_ohci {int* self_id_buffer; } ;

/* Variables and functions */

__attribute__((used)) static int get_self_id_pos(struct fw_ohci *ohci, u32 self_id,
	int self_id_count)
{
	int i;
	u32 entry;

	for (i = 0; i < self_id_count; i++) {
		entry = ohci->self_id_buffer[i];
		if ((self_id & 0xff000000) == (entry & 0xff000000))
			return -1;
		if ((self_id & 0xff000000) < (entry & 0xff000000))
			return i;
	}
	return i;
}
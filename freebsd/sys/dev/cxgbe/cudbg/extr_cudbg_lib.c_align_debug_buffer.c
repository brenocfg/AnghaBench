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
typedef  int u8 ;
struct cudbg_entity_hdr {int start_offset; int num_pad; int size; } ;
struct cudbg_buffer {int offset; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int**,int) ; 

__attribute__((used)) static void align_debug_buffer(struct cudbg_buffer *dbg_buff,
			struct cudbg_entity_hdr *entity_hdr)
{
	u8 zero_buf[4] = {0};
	u8 padding, remain;

	remain = (dbg_buff->offset - entity_hdr->start_offset) % 4;
	padding = 4 - remain;
	if (remain) {
		memcpy(((u8 *) dbg_buff->data) + dbg_buff->offset, &zero_buf,
		       padding);
		dbg_buff->offset += padding;
		entity_hdr->num_pad = padding;
	}

	entity_hdr->size = dbg_buff->offset - entity_hdr->start_offset;
}
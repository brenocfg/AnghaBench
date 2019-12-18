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
typedef  scalar_t__ u32 ;
struct cudbg_buffer {scalar_t__ size; int offset; char* data; } ;

/* Variables and functions */
 int CUDBG_STATUS_NO_SCRATCH_MEM ; 

int get_scratch_buff(struct cudbg_buffer *pdbg_buff, u32 size,
		     struct cudbg_buffer *pscratch_buff)
{
	u32 scratch_offset;
	int rc = 0;

	scratch_offset = pdbg_buff->size - size;

	if (pdbg_buff->offset > (int)scratch_offset || pdbg_buff->size < size) {
		rc = CUDBG_STATUS_NO_SCRATCH_MEM;
		goto err;
	} else {
		pscratch_buff->data = (char *)pdbg_buff->data + scratch_offset;
		pscratch_buff->offset = 0;
		pscratch_buff->size = size;
		pdbg_buff->size -= size;
	}

err:
	return rc;
}
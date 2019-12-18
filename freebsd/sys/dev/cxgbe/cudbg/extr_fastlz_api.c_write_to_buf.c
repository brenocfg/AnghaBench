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

/* Variables and functions */
 int CUDBG_STATUS_OUTBUFF_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (char*,void*,scalar_t__) ; 

int write_to_buf(void *out_buf, u32 out_buf_size, u32 *offset, void *in_buf,
		 u32 in_buf_size)
{
	int rc = 0;

	if (*offset >= out_buf_size) {
		rc = CUDBG_STATUS_OUTBUFF_OVERFLOW;
		goto err;
	}

	memcpy((char *)out_buf + *offset, in_buf, in_buf_size);
	*offset = *offset + in_buf_size;

err:
	return rc;
}
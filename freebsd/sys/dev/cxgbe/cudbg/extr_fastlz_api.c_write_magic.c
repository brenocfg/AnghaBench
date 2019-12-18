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
struct cudbg_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  sixpack_magic ; 
 int write_to_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int write_magic(struct cudbg_buffer *_out_buff)
{
	int rc;

	rc = write_to_buf(_out_buff->data, _out_buff->size, &_out_buff->offset,
			  sixpack_magic, 8);

	return rc;
}
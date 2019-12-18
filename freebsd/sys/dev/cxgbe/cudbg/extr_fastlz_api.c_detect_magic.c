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
 size_t read_from_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 unsigned char* sixpack_magic ; 

int detect_magic(struct cudbg_buffer *_c_buff)
{
	unsigned char buffer[8];
	size_t bytes_read;
	int c;

	bytes_read = read_from_buf(_c_buff->data, _c_buff->size,
				   &_c_buff->offset, buffer, 8);

	if (bytes_read < 8)
		return 0;

	for (c = 0; c < 8; c++)
		if (buffer[c] != sixpack_magic[c])
			return 0;

	return -1;
}
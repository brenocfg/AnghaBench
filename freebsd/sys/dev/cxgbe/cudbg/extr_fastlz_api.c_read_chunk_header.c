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
 int CUDBG_CHUNK_BUF_LEN ; 
 int readU16 (unsigned char*) ; 
 int readU32 (unsigned char*) ; 
 int read_from_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 

int read_chunk_header(struct cudbg_buffer *pc_buff, int *pid, int *poptions,
		      unsigned long *psize, unsigned long *pchecksum,
		      unsigned long *pextra)
{
	unsigned char buffer[CUDBG_CHUNK_BUF_LEN];
	int byte_r = read_from_buf(pc_buff->data, pc_buff->size,
				   &pc_buff->offset, buffer, 16);
	if (byte_r == 0)
		return 0;

	*pid = readU16(buffer) & 0xffff;
	*poptions = readU16(buffer+2) & 0xffff;
	*psize = readU32(buffer+4) & 0xffffffff;
	*pchecksum = readU32(buffer+8) & 0xffffffff;
	*pextra = readU32(buffer+12) & 0xffffffff;
	return 0;
}
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
struct cudbg_buffer {unsigned long size; int /*<<< orphan*/  offset; scalar_t__ data; } ;

/* Variables and functions */
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int strlen (char*) ; 
 unsigned long update_adler32 (unsigned long,...) ; 
 int write_chunk_header (struct cudbg_buffer*,int,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 int write_magic (struct cudbg_buffer*) ; 
 int write_to_buf (scalar_t__,unsigned long,int /*<<< orphan*/ *,...) ; 

int write_compression_hdr(struct cudbg_buffer *pin_buff,
			  struct cudbg_buffer *pout_buff)
{
	struct cudbg_buffer tmp_buffer;
	unsigned long fsize = pin_buff->size;
	unsigned char *buffer;
	unsigned long checksum;
	int rc;
	char *shown_name = "abc";

	/* Always release inner scratch buffer, before releasing outer. */
	rc = get_scratch_buff(pout_buff, 10, &tmp_buffer);

	if (rc)
		goto err;

	buffer = (unsigned char *)tmp_buffer.data;

	rc = write_magic(pout_buff);

	if (rc)
		goto err1;

	/* chunk for File Entry */
	buffer[0] = fsize & 255;
	buffer[1] = (fsize >> 8) & 255;
	buffer[2] = (fsize >> 16) & 255;
	buffer[3] = (fsize >> 24) & 255;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;
	buffer[7] = 0;
	buffer[8] = (strlen(shown_name)+1) & 255;
	buffer[9] = (unsigned char)((strlen(shown_name)+1) >> 8);
	checksum = 1L;
	checksum = update_adler32(checksum, buffer, 10);
	checksum = update_adler32(checksum, shown_name,
				  (int)strlen(shown_name)+1);

	rc = write_chunk_header(pout_buff, 1, 0,
				10+(unsigned long)strlen(shown_name)+1,
				checksum, 0);

	if (rc)
		goto err1;

	rc = write_to_buf(pout_buff->data, pout_buff->size,
			  &(pout_buff->offset), buffer, 10);

	if (rc)
		goto err1;

	rc = write_to_buf(pout_buff->data, pout_buff->size,
			   &(pout_buff->offset), shown_name,
			   (u32)strlen(shown_name)+1);

	if (rc)
		goto err1;

err1:
	release_scratch_buff(&tmp_buffer, pout_buff);
err:
	return rc;
}
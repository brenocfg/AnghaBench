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
typedef  int /*<<< orphan*/  u32 ;
struct cudbg_hdr {int /*<<< orphan*/ * reserved; } ;
struct cudbg_buffer {unsigned int size; unsigned char* data; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUDBG_BLOCK_SIZE ; 
 int fastlz_compress_level (int,unsigned char*,unsigned int,unsigned char*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int /*<<< orphan*/ ,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 unsigned long update_adler32 (long,unsigned char*,unsigned int) ; 
 int write_chunk_header (struct cudbg_buffer*,int,int,unsigned int,unsigned long,unsigned int) ; 
 int write_to_buf (unsigned char*,unsigned int,int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

int compress_buff(struct cudbg_buffer *pin_buff, struct cudbg_buffer *pout_buff)
{
	struct cudbg_buffer tmp_buffer;
	struct cudbg_hdr *cudbg_hdr;
	unsigned long checksum;
	unsigned char *result;
	unsigned int bytes_read;
	int chunk_size, level = 2, rc = 0;
	int compress_method = 1;

	bytes_read = pin_buff->size;
	rc = get_scratch_buff(pout_buff, CUDBG_BLOCK_SIZE, &tmp_buffer);

	if (rc)
		goto err;

	result = (unsigned char *)tmp_buffer.data;

	if (bytes_read < 32)
		compress_method = 0;

	cudbg_hdr = (struct cudbg_hdr *)  pout_buff->data;

	switch (compress_method) {
	case 1:
		chunk_size = fastlz_compress_level(level, pin_buff->data,
						   bytes_read, result);

		checksum = update_adler32(1L, result, chunk_size);

		if ((chunk_size > 62000) && (cudbg_hdr->reserved[7] < (u32)
		    chunk_size))   /* 64512 */
			cudbg_hdr->reserved[7] = (u32) chunk_size;

		rc = write_chunk_header(pout_buff, 17, 1, chunk_size, checksum,
					bytes_read);

		if (rc)
			goto err_put_buff;

		rc = write_to_buf(pout_buff->data, pout_buff->size,
				  &pout_buff->offset, result, chunk_size);

		if (rc)
			goto err_put_buff;

		break;

		/* uncompressed, also fallback method */
	case 0:
	default:
		checksum = update_adler32(1L, pin_buff->data, bytes_read);

		rc = write_chunk_header(pout_buff, 17, 0, bytes_read, checksum,
					bytes_read);

		if (rc)
			goto err_put_buff;

		rc = write_to_buf(pout_buff->data, pout_buff->size,
				  &pout_buff->offset, pin_buff->data,
				  bytes_read);
		if (rc)
			goto err_put_buff;

		break;
	}

err_put_buff:
	release_scratch_buff(&tmp_buffer, pout_buff);
err:
	return rc;
}
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
struct scatterlist {int dummy; } ;
struct atmel_aes_dev {size_t total; size_t datalen; int /*<<< orphan*/ * data; scalar_t__ buf; int /*<<< orphan*/  cpu_transfer_complete; struct scatterlist* real_dst; } ;
typedef  int /*<<< orphan*/  atmel_aes_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atmel_aes_cpu_transfer ; 
 size_t atmel_aes_padlen (size_t,int /*<<< orphan*/ ) ; 
 int atmel_aes_wait_for_data_ready (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atmel_aes_cpu_start(struct atmel_aes_dev *dd,
			       struct scatterlist *src,
			       struct scatterlist *dst,
			       size_t len,
			       atmel_aes_fn_t resume)
{
	size_t padlen = atmel_aes_padlen(len, AES_BLOCK_SIZE);

	if (unlikely(len == 0))
		return -EINVAL;

	sg_copy_to_buffer(src, sg_nents(src), dd->buf, len);

	dd->total = len;
	dd->real_dst = dst;
	dd->cpu_transfer_complete = resume;
	dd->datalen = len + padlen;
	dd->data = (u32 *)dd->buf;
	atmel_aes_write_block(dd, AES_IDATAR(0), dd->data);
	return atmel_aes_wait_for_data_ready(dd, atmel_aes_cpu_transfer);
}
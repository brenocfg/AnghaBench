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
struct atmel_aes_dev {int data; scalar_t__ datalen; int (* resume ) (struct atmel_aes_dev*) ;int (* cpu_transfer_complete ) (struct atmel_aes_dev*) ;int /*<<< orphan*/  total; int /*<<< orphan*/  buf; int /*<<< orphan*/  real_dst; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_IER ; 
 int AES_INT_DATARDY ; 
 int /*<<< orphan*/  AES_ISR ; 
 int /*<<< orphan*/  AES_ODATAR (int /*<<< orphan*/ ) ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 int atmel_aes_read (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_read_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 int stub1 (struct atmel_aes_dev*) ; 

__attribute__((used)) static int atmel_aes_cpu_transfer(struct atmel_aes_dev *dd)
{
	int err = 0;
	u32 isr;

	for (;;) {
		atmel_aes_read_block(dd, AES_ODATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		if (dd->datalen < AES_BLOCK_SIZE)
			break;

		atmel_aes_write_block(dd, AES_IDATAR(0), dd->data);

		isr = atmel_aes_read(dd, AES_ISR);
		if (!(isr & AES_INT_DATARDY)) {
			dd->resume = atmel_aes_cpu_transfer;
			atmel_aes_write(dd, AES_IER, AES_INT_DATARDY);
			return -EINPROGRESS;
		}
	}

	if (!sg_copy_from_buffer(dd->real_dst, sg_nents(dd->real_dst),
				 dd->buf, dd->total))
		err = -EINVAL;

	if (err)
		return atmel_aes_complete(dd, err);

	return dd->cpu_transfer_complete(dd);
}
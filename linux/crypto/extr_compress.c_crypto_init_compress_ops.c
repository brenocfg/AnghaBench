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
struct compress_tfm {int /*<<< orphan*/  cot_decompress; int /*<<< orphan*/  cot_compress; } ;
struct crypto_tfm {struct compress_tfm crt_compress; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_compress ; 
 int /*<<< orphan*/  crypto_decompress ; 

int crypto_init_compress_ops(struct crypto_tfm *tfm)
{
	struct compress_tfm *ops = &tfm->crt_compress;

	ops->cot_compress = crypto_compress;
	ops->cot_decompress = crypto_decompress;

	return 0;
}
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
struct page {int dummy; } ;
struct loop_device {struct crypto_sync_skcipher* key_data; } ;
struct crypto_sync_skcipher {int dummy; } ;
typedef  int sector_t ;
typedef  int (* encdec_cbc_t ) (int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  LOOP_IV_SECTOR_SIZE ; 
 int READ ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int const,unsigned int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cryptoloop_transfer(struct loop_device *lo, int cmd,
		    struct page *raw_page, unsigned raw_off,
		    struct page *loop_page, unsigned loop_off,
		    int size, sector_t IV)
{
	struct crypto_sync_skcipher *tfm = lo->key_data;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);
	struct scatterlist sg_out;
	struct scatterlist sg_in;

	encdec_cbc_t encdecfunc;
	struct page *in_page, *out_page;
	unsigned in_offs, out_offs;
	int err;

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP,
				      NULL, NULL);

	sg_init_table(&sg_out, 1);
	sg_init_table(&sg_in, 1);

	if (cmd == READ) {
		in_page = raw_page;
		in_offs = raw_off;
		out_page = loop_page;
		out_offs = loop_off;
		encdecfunc = crypto_skcipher_decrypt;
	} else {
		in_page = loop_page;
		in_offs = loop_off;
		out_page = raw_page;
		out_offs = raw_off;
		encdecfunc = crypto_skcipher_encrypt;
	}

	while (size > 0) {
		const int sz = min(size, LOOP_IV_SECTOR_SIZE);
		u32 iv[4] = { 0, };
		iv[0] = cpu_to_le32(IV & 0xffffffff);

		sg_set_page(&sg_in, in_page, sz, in_offs);
		sg_set_page(&sg_out, out_page, sz, out_offs);

		skcipher_request_set_crypt(req, &sg_in, &sg_out, sz, iv);
		err = encdecfunc(req);
		if (err)
			goto out;

		IV++;
		size -= sz;
		in_offs += sz;
		out_offs += sz;
	}

	err = 0;

out:
	skcipher_request_zero(req);
	return err;
}
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
typedef  int uint32_t ;
struct enc_param {unsigned char* magic; unsigned char seed; unsigned char* product; unsigned char* version; int datalen; int csum; int /*<<< orphan*/  longstate; int /*<<< orphan*/  key; } ;
typedef  unsigned long ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKLEN (int) ; 
 int ENC_MAGIC_LEN ; 
 int ENC_PRODUCT_LEN ; 
 int ENC_VERSION_LEN ; 
 int /*<<< orphan*/  INCP () ; 
 int bcrypt_buf (unsigned char,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int buffalo_csum (int,unsigned char*,int) ; 
 int check_magic (unsigned char*) ; 
 void* get_be32 (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int decrypt_buf(struct enc_param *ep, unsigned char *data,
		unsigned long datalen)
{
	unsigned char *p;
	uint32_t prod_len;
	uint32_t ver_len;
	uint32_t len;
	uint32_t csum;
	ssize_t remain;
	int err;
	int ret = -1;

#define CHECKLEN(_l) do {		\
	len = (_l);			\
	if (remain < len) {		\
		goto out;		\
	}				\
} while (0)

#define INCP() do {			\
	p += len;			\
	remain -= len;			\
} while (0)

	remain = datalen;
	p = data;

	CHECKLEN(ENC_MAGIC_LEN);
	err = check_magic(p);
	if (err)
		goto out;
	memcpy(ep->magic, p, ENC_MAGIC_LEN);
	INCP();

	CHECKLEN(1);
	ep->seed = *p;
	INCP();

	CHECKLEN(sizeof(uint32_t));
	prod_len = get_be32(p);
	if (prod_len > ENC_PRODUCT_LEN)
		goto out;
	INCP();

	CHECKLEN(prod_len);
	memcpy(ep->product, p, prod_len);
	INCP();

	CHECKLEN(sizeof(uint32_t));
	ver_len = get_be32(p);
	if (ver_len > ENC_VERSION_LEN)
		goto out;
	INCP();

	CHECKLEN(ver_len);
	memcpy(ep->version, p, ver_len);
	INCP();

	CHECKLEN(sizeof(uint32_t));
	ep->datalen = get_be32(p);
	INCP();

	/* decrypt data */
	CHECKLEN(ep->datalen);
	err = bcrypt_buf(ep->version[0], ep->key, p, data, ep->datalen,
			 ep->longstate);
	if (err)
		goto out;
	INCP();

	CHECKLEN(sizeof(uint32_t));
	ep->csum = get_be32(p);
	INCP();

	csum = buffalo_csum(ep->datalen, data, ep->datalen);
	if (csum != ep->csum)
		goto out;

	/* decrypt product name */
	err = bcrypt_buf(ep->product[0], ep->key, ep->version, ep->version,
			 ver_len, ep->longstate);
	if (err)
		goto out;

	/* decrypt version */
	err = bcrypt_buf(ep->seed, ep->key, ep->product, ep->product, prod_len,
			 ep->longstate);
	if (err)
		goto out;

	ret = 0;
out:
	return ret;

#undef CHECKLEN
#undef INCP
}
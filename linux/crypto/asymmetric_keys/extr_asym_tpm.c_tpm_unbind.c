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
struct tpm_buf {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 int LOAD32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int SHA1_DIGEST_SIZE ; 
 scalar_t__ TPM_DATA_OFFSET ; 
 int TPM_NONCE_SIZE ; 
 int TPM_ORD_UNBIND ; 
 int /*<<< orphan*/  TPM_TAG_RQU_AUTH1_COMMAND ; 
 int TPM_UNBIND_SIZE ; 
 int TSS_authhmac (unsigned char*,unsigned char*,int,unsigned char*,unsigned char*,unsigned char,int,int*,int,int*,int,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TSS_checkhmac1 (scalar_t__,int,unsigned char*,unsigned char*,int,int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int oiap (struct tpm_buf*,int*,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  store8 (struct tpm_buf*,unsigned char) ; 
 int /*<<< orphan*/  storebytes (struct tpm_buf*,unsigned char const*,int) ; 
 int tpm_get_random (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int trusted_tpm_send (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_unbind(struct tpm_buf *tb,
			uint32_t keyhandle, unsigned char *keyauth,
			const unsigned char *blob, uint32_t bloblen,
			void *out, uint32_t outlen)
{
	unsigned char nonceodd[TPM_NONCE_SIZE];
	unsigned char enonce[TPM_NONCE_SIZE];
	unsigned char authdata[SHA1_DIGEST_SIZE];
	uint32_t authhandle = 0;
	unsigned char cont = 0;
	uint32_t ordinal;
	uint32_t datalen;
	int ret;

	ordinal = htonl(TPM_ORD_UNBIND);
	datalen = htonl(bloblen);

	/* session for loading the key */
	ret = oiap(tb, &authhandle, enonce);
	if (ret < 0) {
		pr_info("oiap failed (%d)\n", ret);
		return ret;
	}

	/* generate odd nonce */
	ret = tpm_get_random(NULL, nonceodd, TPM_NONCE_SIZE);
	if (ret < 0) {
		pr_info("tpm_get_random failed (%d)\n", ret);
		return ret;
	}

	/* calculate authorization HMAC value */
	ret = TSS_authhmac(authdata, keyauth, SHA1_DIGEST_SIZE, enonce,
			   nonceodd, cont, sizeof(uint32_t), &ordinal,
			   sizeof(uint32_t), &datalen,
			   bloblen, blob, 0, 0);
	if (ret < 0)
		return ret;

	/* build the request buffer */
	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_AUTH1_COMMAND);
	store32(tb, TPM_UNBIND_SIZE + bloblen);
	store32(tb, TPM_ORD_UNBIND);
	store32(tb, keyhandle);
	store32(tb, bloblen);
	storebytes(tb, blob, bloblen);
	store32(tb, authhandle);
	storebytes(tb, nonceodd, TPM_NONCE_SIZE);
	store8(tb, cont);
	storebytes(tb, authdata, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (ret < 0) {
		pr_info("authhmac failed (%d)\n", ret);
		return ret;
	}

	datalen = LOAD32(tb->data, TPM_DATA_OFFSET);

	ret = TSS_checkhmac1(tb->data, ordinal, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     sizeof(uint32_t), TPM_DATA_OFFSET,
			     datalen, TPM_DATA_OFFSET + sizeof(uint32_t),
			     0, 0);
	if (ret < 0) {
		pr_info("TSS_checkhmac1 failed (%d)\n", ret);
		return ret;
	}

	memcpy(out, tb->data + TPM_DATA_OFFSET + sizeof(uint32_t),
	       min(outlen, datalen));

	return datalen;
}
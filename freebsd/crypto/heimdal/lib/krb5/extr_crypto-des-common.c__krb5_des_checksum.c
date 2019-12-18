#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_data {TYPE_1__* schedule; } ;
struct _krb5_evp_schedule {int /*<<< orphan*/  ectx; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  ivec ;
struct TYPE_6__ {unsigned char* data; } ;
struct TYPE_7__ {TYPE_2__ checksum; } ;
struct TYPE_5__ {struct _krb5_evp_schedule* data; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  DES_cblock ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ ,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_generate_random_block (unsigned char*,int) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

krb5_error_code
_krb5_des_checksum(krb5_context context,
		   const EVP_MD *evp_md,
		   struct _krb5_key_data *key,
		   const void *data,
		   size_t len,
		   Checksum *cksum)
{
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    EVP_MD_CTX *m;
    DES_cblock ivec;
    unsigned char *p = cksum->checksum.data;

    krb5_generate_random_block(p, 8);

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    EVP_DigestInit_ex(m, evp_md, NULL);
    EVP_DigestUpdate(m, p, 8);
    EVP_DigestUpdate(m, data, len);
    EVP_DigestFinal_ex (m, p + 8, NULL);
    EVP_MD_CTX_destroy(m);
    memset (&ivec, 0, sizeof(ivec));
    EVP_CipherInit_ex(ctx->ectx, NULL, NULL, NULL, (void *)&ivec, -1);
    EVP_Cipher(ctx->ectx, p, p, 24);

    return 0;
}
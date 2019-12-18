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
struct ntlmv2_key {unsigned char* signkey; int /*<<< orphan*/  sealkey; int /*<<< orphan*/ * signsealkey; scalar_t__ seq; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,unsigned char*) ; 
 char* a2i_sealmagic ; 
 char* a2i_signmagic ; 
 char* i2a_sealmagic ; 
 char* i2a_signmagic ; 
 int strlen (char const*) ; 

void
_gss_ntlm_set_key(struct ntlmv2_key *key, int acceptor, int sealsign,
		  unsigned char *data, size_t len)
{
    unsigned char out[16];
    EVP_MD_CTX *ctx;
    const char *signmagic;
    const char *sealmagic;

    if (acceptor) {
	signmagic = a2i_signmagic;
	sealmagic = a2i_sealmagic;
    } else {
	signmagic = i2a_signmagic;
	sealmagic = i2a_sealmagic;
    }

    key->seq = 0;

    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
    EVP_DigestUpdate(ctx, data, len);
    EVP_DigestUpdate(ctx, signmagic, strlen(signmagic) + 1);
    EVP_DigestFinal_ex(ctx, key->signkey, NULL);

    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
    EVP_DigestUpdate(ctx, data, len);
    EVP_DigestUpdate(ctx, sealmagic, strlen(sealmagic) + 1);
    EVP_DigestFinal_ex(ctx, out, NULL);
    EVP_MD_CTX_destroy(ctx);

    RC4_set_key(&key->sealkey, 16, out);
    if (sealsign)
	key->signsealkey = &key->sealkey;
}
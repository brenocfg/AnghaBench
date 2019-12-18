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
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int
heim_ntlm_derive_ntlm2_sess(const unsigned char sessionkey[16],
			    const unsigned char *clnt_nonce, size_t clnt_nonce_length,
			    const unsigned char svr_chal[8],
			    unsigned char derivedkey[16])
{
    unsigned int hmaclen;
    HMAC_CTX *c;

    /* HMAC(Ksession, serverchallenge || clientchallenge) */
    c = HMAC_CTX_new();
    if (c == NULL)
	return ENOMEM;
    HMAC_Init_ex(c, sessionkey, 16, EVP_md5(), NULL);
    HMAC_Update(c, svr_chal, 8);
    HMAC_Update(c, clnt_nonce, clnt_nonce_length);
    HMAC_Final(c, derivedkey, &hmaclen);
    HMAC_CTX_free(c);
    return 0;
}
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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int
heim_ntlm_calculate_ntlm2_sess_hash(const unsigned char clnt_nonce[8],
				    const unsigned char svr_chal[8],
				    unsigned char verifier[8])
{
    unsigned char ntlm2_sess_hash[MD5_DIGEST_LENGTH];
    EVP_MD_CTX *m;

    m = EVP_MD_CTX_create();
    if (m == NULL)
	return ENOMEM;

    EVP_DigestInit_ex(m, EVP_md5(), NULL);
    EVP_DigestUpdate(m, svr_chal, 8); /* session nonce part 1 */
    EVP_DigestUpdate(m, clnt_nonce, 8); /* session nonce part 2 */
    EVP_DigestFinal_ex(m, ntlm2_sess_hash, NULL); /* will only use first 8 bytes */
    EVP_MD_CTX_destroy(m);

    memcpy(verifier, ntlm2_sess_hash, 8);

    return 0;
}
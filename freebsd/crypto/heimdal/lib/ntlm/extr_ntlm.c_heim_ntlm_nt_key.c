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
struct ntlm_buf {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md4 () ; 
 int /*<<< orphan*/  MD5_DIGEST_LENGTH ; 
 int ascii2ucs2le (char const*,int /*<<< orphan*/ ,struct ntlm_buf*) ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

int
heim_ntlm_nt_key(const char *password, struct ntlm_buf *key)
{
    struct ntlm_buf buf;
    EVP_MD_CTX *m;
    int ret;

    key->data = malloc(MD5_DIGEST_LENGTH);
    if (key->data == NULL)
	return ENOMEM;
    key->length = MD5_DIGEST_LENGTH;

    ret = ascii2ucs2le(password, 0, &buf);
    if (ret) {
	heim_ntlm_free_buf(key);
	return ret;
    }

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	heim_ntlm_free_buf(key);
	heim_ntlm_free_buf(&buf);
	return ENOMEM;
    }

    EVP_DigestInit_ex(m, EVP_md4(), NULL);
    EVP_DigestUpdate(m, buf.data, buf.length);
    EVP_DigestFinal_ex(m, key->data, NULL);
    EVP_MD_CTX_destroy(m);

    heim_ntlm_free_buf(&buf);
    return 0;
}
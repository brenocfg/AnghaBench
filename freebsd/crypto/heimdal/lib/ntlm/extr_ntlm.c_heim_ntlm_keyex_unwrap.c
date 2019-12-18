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
struct ntlm_buf {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_rc4 () ; 
 int HNTLM_ERR_CRYPTO ; 
 int HNTLM_ERR_INVALID_LENGTH ; 
 scalar_t__ MD4_DIGEST_LENGTH ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ntlm_buf*,int /*<<< orphan*/ ,int) ; 

int
heim_ntlm_keyex_unwrap(struct ntlm_buf *baseKey,
		       struct ntlm_buf *encryptedSession,
		       struct ntlm_buf *session)
{
    EVP_CIPHER_CTX *c;

    memset(session, 0, sizeof(*session));

    if (baseKey->length != MD4_DIGEST_LENGTH)
	return HNTLM_ERR_INVALID_LENGTH;

    session->length = MD4_DIGEST_LENGTH;
    session->data = malloc(session->length);
    if (session->data == NULL) {
	session->length = 0;
	return ENOMEM;
    }
    c = EVP_CIPHER_CTX_new();
    if (c == NULL) {
	heim_ntlm_free_buf(session);
	return ENOMEM;
    }

    if (EVP_CipherInit_ex(c, EVP_rc4(), NULL, baseKey->data, NULL, 0) != 1) {
	EVP_CIPHER_CTX_free(c);
	heim_ntlm_free_buf(session);
	return HNTLM_ERR_CRYPTO;
    }

    EVP_Cipher(c, session->data, encryptedSession->data, session->length);
    EVP_CIPHER_CTX_free(c);

    return 0;
}
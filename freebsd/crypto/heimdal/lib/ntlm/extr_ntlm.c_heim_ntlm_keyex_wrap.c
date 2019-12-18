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
struct ntlm_buf {void* length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_rc4 () ; 
 int HNTLM_ERR_CRYPTO ; 
 int HNTLM_ERR_RAND ; 
 void* MD4_DIGEST_LENGTH ; 
 int RAND_bytes (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 void* malloc (void*) ; 

int
heim_ntlm_keyex_wrap(struct ntlm_buf *base_session,
		     struct ntlm_buf *session,
		     struct ntlm_buf *encryptedSession)
{
    EVP_CIPHER_CTX *c;
    int ret;

    session->length = MD4_DIGEST_LENGTH;
    session->data = malloc(session->length);
    if (session->data == NULL) {
	session->length = 0;
	return ENOMEM;
    }
    encryptedSession->length = MD4_DIGEST_LENGTH;
    encryptedSession->data = malloc(encryptedSession->length);
    if (encryptedSession->data == NULL) {
	heim_ntlm_free_buf(session);
	encryptedSession->length = 0;
	return ENOMEM;
    }

    c = EVP_CIPHER_CTX_new();
    if (c == NULL) {
	heim_ntlm_free_buf(encryptedSession);
	heim_ntlm_free_buf(session);
	return ENOMEM;
    }

    ret = EVP_CipherInit_ex(c, EVP_rc4(), NULL, base_session->data, NULL, 1);
    if (ret != 1) {
	EVP_CIPHER_CTX_free(c);
	heim_ntlm_free_buf(encryptedSession);
	heim_ntlm_free_buf(session);
	return HNTLM_ERR_CRYPTO;
    }

    if (RAND_bytes(session->data, session->length) != 1) {
	EVP_CIPHER_CTX_free(c);
	heim_ntlm_free_buf(encryptedSession);
	heim_ntlm_free_buf(session);
	return HNTLM_ERR_RAND;
    }

    EVP_Cipher(c, encryptedSession->data, session->data, encryptedSession->length);
    EVP_CIPHER_CTX_free(c);

    return 0;



}
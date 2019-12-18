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
struct ntlm_buf {int /*<<< orphan*/ * data; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md4 () ; 
 scalar_t__ MD4_DIGEST_LENGTH ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 

int
heim_ntlm_v1_base_session(void *key, size_t len,
			  struct ntlm_buf *session)
{
    EVP_MD_CTX *m;

    session->length = MD4_DIGEST_LENGTH;
    session->data = malloc(session->length);
    if (session->data == NULL) {
	session->length = 0;
	return ENOMEM;
    }

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	heim_ntlm_free_buf(session);
	return ENOMEM;
    }
    EVP_DigestInit_ex(m, EVP_md4(), NULL);
    EVP_DigestUpdate(m, key, len);
    EVP_DigestFinal_ex(m, session->data, NULL);
    EVP_MD_CTX_destroy(m);

    return 0;
}
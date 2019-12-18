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
struct ntlm_buf {int length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int HNTLM_ERR_INVALID_LENGTH ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

int
heim_ntlm_v2_base_session(void *key, size_t len,
			  struct ntlm_buf *ntlmResponse,
			  struct ntlm_buf *session)
{
    unsigned int hmaclen;
    HMAC_CTX *c;

    if (ntlmResponse->length <= 16)
        return HNTLM_ERR_INVALID_LENGTH;

    session->data = malloc(16);
    if (session->data == NULL)
	return ENOMEM;
    session->length = 16;

    /* Note: key is the NTLMv2 key */
    c = HMAC_CTX_new();
    if (c == NULL) {
	heim_ntlm_free_buf(session);
	return ENOMEM;
    }
    HMAC_Init_ex(c, key, len, EVP_md5(), NULL);
    HMAC_Update(c, ntlmResponse->data, 16);
    HMAC_Final(c, session->data, &hmaclen);
    HMAC_CTX_free(c);

    return 0;
}
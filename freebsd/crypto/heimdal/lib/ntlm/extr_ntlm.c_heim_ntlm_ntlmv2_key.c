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
struct ntlm_buf {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ascii2ucs2le (char const*,int,struct ntlm_buf*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

int
heim_ntlm_ntlmv2_key(const void *key, size_t len,
		     const char *username,
		     const char *target,
		     unsigned char ntlmv2[16])
{
    int ret;
    unsigned int hmaclen;
    HMAC_CTX *c;

    c = HMAC_CTX_new();
    if (c == NULL)
	return ENOMEM;
    HMAC_Init_ex(c, key, len, EVP_md5(), NULL);
    {
	struct ntlm_buf buf;
	/* uppercase username and turn it into ucs2-le */
	ret = ascii2ucs2le(username, 1, &buf);
	if (ret)
	    goto out;
	HMAC_Update(c, buf.data, buf.length);
	free(buf.data);
	/* uppercase target and turn into ucs2-le */
	ret = ascii2ucs2le(target, 1, &buf);
	if (ret)
	    goto out;
	HMAC_Update(c, buf.data, buf.length);
	free(buf.data);
    }
    HMAC_Final(c, ntlmv2, &hmaclen);
 out:
    HMAC_CTX_free(c);

    return ret;
}
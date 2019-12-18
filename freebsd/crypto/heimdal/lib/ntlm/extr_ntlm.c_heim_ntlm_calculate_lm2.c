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
typedef  int /*<<< orphan*/  uint8_t ;
struct ntlm_buf {int length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  clientchallenge ;

/* Variables and functions */
 int ENOMEM ; 
 int HNTLM_ERR_RAND ; 
 int RAND_bytes (unsigned char*,int) ; 
 int heim_ntlm_derive_ntlm2_sess (unsigned char*,unsigned char*,int,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_ntlm_ntlmv2_key (void const*,size_t,char const*,char const*,unsigned char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

int
heim_ntlm_calculate_lm2(const void *key, size_t len,
			const char *username,
			const char *target,
			const unsigned char serverchallenge[8],
			unsigned char ntlmv2[16],
			struct ntlm_buf *answer)
{
    unsigned char clientchallenge[8];
    int ret;

    if (RAND_bytes(clientchallenge, sizeof(clientchallenge)) != 1)
	return HNTLM_ERR_RAND;

    /* calculate ntlmv2 key */

    heim_ntlm_ntlmv2_key(key, len, username, target, ntlmv2);

    answer->data = malloc(24);
    if (answer->data == NULL)
        return ENOMEM;
    answer->length = 24;

    ret = heim_ntlm_derive_ntlm2_sess(ntlmv2, clientchallenge, 8,
				serverchallenge, answer->data);
    if (ret)
	return ret;

    memcpy(((uint8_t *)answer->data) + 16, clientchallenge, 8);

    return 0;
}
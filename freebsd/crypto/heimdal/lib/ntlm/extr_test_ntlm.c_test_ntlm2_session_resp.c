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
struct ntlm_buf {int length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int heim_ntlm_calculate_ntlm2_sess (unsigned char const*,unsigned char const*,unsigned char const*,struct ntlm_buf*,struct ntlm_buf*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static int
test_ntlm2_session_resp(void)
{
    int ret;
    struct ntlm_buf lm, ntlm;

    const unsigned char lm_resp[24] =
	"\xff\xff\xff\x00\x11\x22\x33\x44"
	"\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";
    const unsigned char ntlm2_sess_resp[24] =
	"\x10\xd5\x50\x83\x2d\x12\xb2\xcc"
	"\xb7\x9d\x5a\xd1\xf4\xee\xd3\xdf"
	"\x82\xac\xa4\xc3\x68\x1d\xd4\x55";

    const unsigned char client_nonce[8] =
	"\xff\xff\xff\x00\x11\x22\x33\x44";
    const unsigned char server_challenge[8] =
	"\x01\x23\x45\x67\x89\xab\xcd\xef";

    const unsigned char ntlm_hash[16] =
	"\xcd\x06\xca\x7c\x7e\x10\xc9\x9b"
	"\x1d\x33\xb7\x48\x5a\x2e\xd8\x08";

    ret = heim_ntlm_calculate_ntlm2_sess(client_nonce,
					 server_challenge,
					 ntlm_hash,
					 &lm,
					 &ntlm);
    if (ret)
	errx(1, "heim_ntlm_calculate_ntlm2_sess_resp");

    if (lm.length != 24 || memcmp(lm.data, lm_resp, 24) != 0)
	errx(1, "lm_resp wrong");
    if (ntlm.length != 24 || memcmp(ntlm.data, ntlm2_sess_resp, 24) != 0)
	errx(1, "ntlm2_sess_resp wrong");

    free(lm.data);
    free(ntlm.data);


    return 0;
}
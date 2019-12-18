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
struct ntlm_buf {int length; char* data; } ;
typedef  int /*<<< orphan*/  ntlmv2 ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int heim_ntlm_calculate_ntlm2 (char*,int,char const*,char const*,unsigned char const*,struct ntlm_buf*,unsigned char*,struct ntlm_buf*) ; 
 int /*<<< orphan*/  heim_ntlm_nt_key (char const*,struct ntlm_buf*) ; 
 int heim_ntlm_verify_ntlm2 (char*,int,char const*,char const*,int /*<<< orphan*/ ,unsigned char const*,struct ntlm_buf*,struct ntlm_buf*,unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int
test_keys(void)
{
    const char
	*username = "test",
	*password = "test1234",
	*target = "TESTNT";
    const unsigned char
	serverchallenge[8] = "\x67\x7f\x1c\x55\x7a\x5e\xe9\x6c";
    struct ntlm_buf infotarget, infotarget2, answer, key;
    unsigned char ntlmv2[16], ntlmv2_1[16];
    int ret;

    infotarget.length = 70;
    infotarget.data =
	"\x02\x00\x0c\x00\x54\x00\x45\x00\x53\x00\x54\x00\x4e\x00\x54\x00"
	"\x01\x00\x0c\x00\x4d\x00\x45\x00\x4d\x00\x42\x00\x45\x00\x52\x00"
	"\x03\x00\x1e\x00\x6d\x00\x65\x00\x6d\x00\x62\x00\x65\x00\x72\x00"
	    "\x2e\x00\x74\x00\x65\x00\x73\x00\x74\x00\x2e\x00\x63\x00\x6f"
	    "\x00\x6d\x00"
	"\x00\x00\x00\x00";

    answer.length = 0;
    answer.data = NULL;

    heim_ntlm_nt_key(password, &key);

    ret = heim_ntlm_calculate_ntlm2(key.data,
				    key.length,
				    username,
				    target,
				    serverchallenge,
				    &infotarget,
				    ntlmv2,
				    &answer);
    if (ret)
	errx(1, "heim_ntlm_calculate_ntlm2");

    ret = heim_ntlm_verify_ntlm2(key.data,
				 key.length,
				 username,
				 target,
				 0,
				 serverchallenge,
				 &answer,
				 &infotarget2,
				 ntlmv2_1);
    if (ret)
	errx(1, "heim_ntlm_verify_ntlm2");

    if (memcmp(ntlmv2, ntlmv2_1, sizeof(ntlmv2)) != 0)
	errx(1, "ntlm master key not same");

    if (infotarget.length > infotarget2.length)
	errx(1, "infotarget length");

    if (memcmp(infotarget.data, infotarget2.data, infotarget.length) != 0)
	errx(1, "infotarget not the same");

    free(key.data);
    free(answer.data);
    free(infotarget2.data);

    return 0;
}
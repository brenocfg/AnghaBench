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
typedef  int /*<<< orphan*/  ti ;
struct ntlm_targetinfo {int avflags; int /*<<< orphan*/ * dnsservername; } ;
struct ntlm_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int heim_ntlm_decode_targetinfo (struct ntlm_buf*,int,struct ntlm_targetinfo*) ; 
 int heim_ntlm_encode_targetinfo (struct ntlm_targetinfo*,int,struct ntlm_buf*) ; 
 int /*<<< orphan*/  heim_ntlm_free_targetinfo (struct ntlm_targetinfo*) ; 
 int /*<<< orphan*/  memset (struct ntlm_targetinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rk_UNCONST (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
test_targetinfo(void)
{
    struct ntlm_targetinfo ti;
    struct ntlm_buf buf;
    const char *dnsservername = "dnsservername";
    int ret;

    memset(&ti, 0, sizeof(ti));

    ti.dnsservername = rk_UNCONST(dnsservername);
    ti.avflags = 1;
    ret = heim_ntlm_encode_targetinfo(&ti, 1, &buf);
    if (ret)
	return ret;

    memset(&ti, 0, sizeof(ti));

    ret = heim_ntlm_decode_targetinfo(&buf, 1, &ti);
    if (ret)
	return ret;

    if (ti.dnsservername == NULL ||
	strcmp(ti.dnsservername, dnsservername) != 0)
	errx(1, "ti.dnshostname != %s", dnsservername);
    if (ti.avflags != 1)
	errx(1, "ti.avflags != 1");

    heim_ntlm_free_targetinfo(&ti);

    return 0;
}
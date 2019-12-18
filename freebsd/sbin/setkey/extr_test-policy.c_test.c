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
typedef  int /*<<< orphan*/  getbuf ;

/* Variables and functions */
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPV6_IPSEC_POLICY ; 
 int IP_IPSEC_POLICY ; 
 int /*<<< orphan*/  PFKEY_EXTLEN (char*) ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getsockopt (int,int,int,char*,int*) ; 
 char* ipsec_dump_policy (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipsec_strerror () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setsockopt (int,int,int,char*,int /*<<< orphan*/ ) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int test(char *policy, int family)
{
	int so, proto, optname;
	int len;
	char getbuf[1024];

	switch (family) {
	case PF_INET:
		proto = IPPROTO_IP;
		optname = IP_IPSEC_POLICY;
		break;
	case PF_INET6:
		proto = IPPROTO_IPV6;
		optname = IPV6_IPSEC_POLICY;
		break;
	}

	if ((so = socket(family, SOCK_DGRAM, 0)) < 0)
		perror("socket");

	if (setsockopt(so, proto, optname, policy, PFKEY_EXTLEN(policy)) < 0)
		perror("setsockopt");

	len = sizeof(getbuf);
	memset(getbuf, 0, sizeof(getbuf));
	if (getsockopt(so, proto, optname, getbuf, &len) < 0)
		perror("getsockopt");

    {
	char *buf = NULL;

	printf("\tgetlen:%d\n", len);

	if ((buf = ipsec_dump_policy(getbuf, NULL)) == NULL)
		ipsec_strerror();
	else
		printf("\t[%s]\n", buf);

	free(buf);
    }

	close (so);
}
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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct mld_hdr {int mld_type; int /*<<< orphan*/  mld_addr; } ;
typedef  int /*<<< orphan*/  ntop_buf ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
#define  ICMP6_MEMBERSHIP_QUERY 130 
#define  ICMP6_MEMBERSHIP_REDUCTION 129 
#define  ICMP6_MEMBERSHIP_REPORT 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  stdout ; 

void
dump(int s)
{
	int i;
	struct mld_hdr *mld;
	u_char buf[1024];
	struct sockaddr_in6 from;
	int from_len = sizeof(from);
	char ntop_buf[256];

	if ((i = recvfrom(s, buf, sizeof(buf), 0,
			  (struct sockaddr *)&from,
			  &from_len)) < 0)
		return;

	if (i < sizeof(struct mld_hdr)) {
		printf("too short!\n");
		return;
	}

	mld = (struct mld_hdr *)buf;

	printf("from %s, ", inet_ntop(AF_INET6, &from.sin6_addr,
				      ntop_buf, sizeof(ntop_buf)));

	switch (mld->mld_type) {
	case ICMP6_MEMBERSHIP_QUERY:
		printf("type=Multicast Listener Query, ");
		break;
	case ICMP6_MEMBERSHIP_REPORT:
		printf("type=Multicast Listener Report, ");
		break;
	case ICMP6_MEMBERSHIP_REDUCTION:
		printf("type=Multicast Listener Done, ");
		break;
	}
	printf("addr=%s\n", inet_ntop(AF_INET6, &mld->mld_addr,
				    ntop_buf, sizeof(ntop_buf)));
	
	fflush(stdout);
}
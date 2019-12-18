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
struct in6_addrpolicy {void* label; void* preced; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SIOCAADDRCTL_POLICY ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct in6_addrpolicy*) ; 
 int /*<<< orphan*/  memset (struct in6_addrpolicy*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_prefix (char const*,struct in6_addrpolicy*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_policy(char *prefix, char *prec, char *label)
{
	struct in6_addrpolicy p;
	int s;

	memset(&p, 0, sizeof(p));

	if (parse_prefix((const char *)prefix, &p))
		errx(1, "bad prefix: %s", prefix);
	p.preced = atoi(prec);
	p.label = atoi(label);

	if ((s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		err(1, "socket(UDP)");
	if (ioctl(s, SIOCAADDRCTL_POLICY, &p))
		err(1, "ioctl(SIOCAADDRCTL_POLICY)");

	close(s);
}
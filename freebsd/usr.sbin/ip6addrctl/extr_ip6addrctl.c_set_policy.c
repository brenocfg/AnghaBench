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
struct policyqueue {int /*<<< orphan*/  pc_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SIOCAADDRCTL_POLICY ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 struct policyqueue* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct policyqueue* TAILQ_NEXT (struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc_entry ; 
 int /*<<< orphan*/  policyhead ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
set_policy(void)
{
	struct policyqueue *ent;
	int s;

	if ((s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		err(1, "socket(UDP)");

	for (ent = TAILQ_FIRST(&policyhead); ent;
	     ent = TAILQ_NEXT(ent, pc_entry)) {
		if (ioctl(s, SIOCAADDRCTL_POLICY, &ent->pc_policy))
			warn("ioctl(SIOCAADDRCTL_POLICY)");
	}

	close(s);
}
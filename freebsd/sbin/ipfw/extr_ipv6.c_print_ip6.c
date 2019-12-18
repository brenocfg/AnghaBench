#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  trad ;
struct in6_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_name; } ;
struct buf_pr {int dummy; } ;
struct TYPE_5__ {scalar_t__ opcode; } ;
struct TYPE_6__ {TYPE_1__ o; struct in6_addr addr6; } ;
typedef  TYPE_2__ ipfw_insn_ip6 ;
typedef  int /*<<< orphan*/  ipfw_insn ;
struct TYPE_7__ {scalar_t__ do_resolv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int F_LEN (int /*<<< orphan*/ *) ; 
 scalar_t__ O_IP6 ; 
 scalar_t__ O_IP6_DST ; 
 scalar_t__ O_IP6_DST_ME ; 
 scalar_t__ O_IP6_SRC ; 
 scalar_t__ O_IP6_SRC_ME ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,...) ; 
 TYPE_4__ co ; 
 int contigmask (int /*<<< orphan*/ *,int) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 

void
print_ip6(struct buf_pr *bp, ipfw_insn_ip6 *cmd)
{
	char trad[255];
	struct hostent *he = NULL;
	struct in6_addr *a = &(cmd->addr6);
	int len, mb;

	len = F_LEN((ipfw_insn *) cmd) - 1;
	if (cmd->o.opcode == O_IP6_SRC_ME || cmd->o.opcode == O_IP6_DST_ME) {
		bprintf(bp, " me6");
		return;
	}
	if (cmd->o.opcode == O_IP6) {
		bprintf(bp, " ip6");
		return;
	}

	/*
	 * len == 4 indicates a single IP, whereas lists of 1 or more
	 * addr/mask pairs have len = (2n+1). We convert len to n so we
	 * use that to count the number of entries.
	 */
	bprintf(bp, " ");
	for (len = len / 4; len > 0; len -= 2, a += 2) {
		/* mask length */
		mb = (cmd->o.opcode == O_IP6_SRC ||
		    cmd->o.opcode == O_IP6_DST) ?  128:
		    contigmask((uint8_t *)&(a[1]), 128);

		if (mb == 128 && co.do_resolv)
			he = gethostbyaddr((char *)a, sizeof(*a), AF_INET6);

		if (he != NULL)	     /* resolved to name */
			bprintf(bp, "%s", he->h_name);
		else if (mb == 0)	   /* any */
			bprintf(bp, "any");
		else {	  /* numeric IP followed by some kind of mask */
			if (inet_ntop(AF_INET6,  a, trad,
			    sizeof(trad)) == NULL)
				bprintf(bp, "Error ntop in print_ip6\n");
			bprintf(bp, "%s",  trad );
			if (mb < 0) /* mask not contiguous */
				bprintf(bp, "/%s", inet_ntop(AF_INET6, &a[1],
				    trad, sizeof(trad)));
			else if (mb < 128)
				bprintf(bp, "/%d", mb);
		}
		if (len > 2)
			bprintf(bp, ",");
	}
}
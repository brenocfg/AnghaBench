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
struct ifbareq {char* ifba_vlan; int /*<<< orphan*/  ifba_flags; int /*<<< orphan*/  ifba_expire; int /*<<< orphan*/  ifba_ifsname; int /*<<< orphan*/  ifba_dst; } ;
struct ifbaconf {int ifbac_len; char* ifbac_buf; struct ifbareq* ifbac_req; } ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
typedef  int /*<<< orphan*/  ifbac ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGRTS ; 
 int /*<<< orphan*/  IFBAFBITS ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbaconf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ether_ntoa (struct ether_addr*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static void
bridge_addresses(int s, const char *prefix)
{
	struct ifbaconf ifbac;
	struct ifbareq *ifba;
	char *inbuf = NULL, *ninbuf;
	int i, len = 8192;
	struct ether_addr ea;

	for (;;) {
		ninbuf = realloc(inbuf, len);
		if (ninbuf == NULL)
			err(1, "unable to allocate address buffer");
		ifbac.ifbac_len = len;
		ifbac.ifbac_buf = inbuf = ninbuf;
		if (do_cmd(s, BRDGRTS, &ifbac, sizeof(ifbac), 0) < 0)
			err(1, "unable to get address cache");
		if ((ifbac.ifbac_len + sizeof(*ifba)) < len)
			break;
		len *= 2;
	}

	for (i = 0; i < ifbac.ifbac_len / sizeof(*ifba); i++) {
		ifba = ifbac.ifbac_req + i;
		memcpy(ea.octet, ifba->ifba_dst,
		    sizeof(ea.octet));
		printf("%s%s Vlan%d %s %lu ", prefix, ether_ntoa(&ea),
		    ifba->ifba_vlan, ifba->ifba_ifsname, ifba->ifba_expire);
		printb("flags", ifba->ifba_flags, IFBAFBITS);
		printf("\n");
	}

	free(inbuf);
}
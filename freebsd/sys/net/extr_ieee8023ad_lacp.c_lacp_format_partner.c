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
typedef  int /*<<< orphan*/  sysid ;
struct lacp_peerinfo {int /*<<< orphan*/  lip_portid; int /*<<< orphan*/  lip_key; int /*<<< orphan*/  lip_systemid; } ;
typedef  int /*<<< orphan*/  portid ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_PORTIDSTR_MAX ; 
 int /*<<< orphan*/  LACP_SYSTEMIDSTR_MAX ; 
 char* lacp_format_portid (int /*<<< orphan*/ *,char*,int) ; 
 char* lacp_format_systemid (int /*<<< orphan*/ *,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int,char*) ; 

const char *
lacp_format_partner(const struct lacp_peerinfo *peer, char *buf, size_t buflen)
{
	char sysid[LACP_SYSTEMIDSTR_MAX+1];
	char portid[LACP_PORTIDSTR_MAX+1];

	snprintf(buf, buflen, "(%s,%04X,%s)",
	    lacp_format_systemid(&peer->lip_systemid, sysid, sizeof(sysid)),
	    ntohs(peer->lip_key),
	    lacp_format_portid(&peer->lip_portid, portid, sizeof(portid)));

	return (buf);
}
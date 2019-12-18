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
struct lacp_systemid {int /*<<< orphan*/  lsi_mac; int /*<<< orphan*/  lsi_prio; } ;
typedef  int /*<<< orphan*/  macbuf ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_MACSTR_MAX ; 
 char* lacp_format_mac (int /*<<< orphan*/ ,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,char*) ; 

const char *
lacp_format_systemid(const struct lacp_systemid *sysid,
    char *buf, size_t buflen)
{
	char macbuf[LACP_MACSTR_MAX+1];

	snprintf(buf, buflen, "%04X,%s",
	    ntohs(sysid->lsi_prio),
	    lacp_format_mac(sysid->lsi_mac, macbuf, sizeof(macbuf)));

	return (buf);
}
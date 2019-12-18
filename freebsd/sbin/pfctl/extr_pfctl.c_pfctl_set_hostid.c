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
typedef  int /*<<< orphan*/  u_int32_t ;
struct pfctl {int hostid_set; int opts; int /*<<< orphan*/  hostid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTONL (int /*<<< orphan*/ ) ; 
 int PFCTL_FLAG_OPTION ; 
 int PF_OPT_VERBOSE ; 
 int loadopt ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
pfctl_set_hostid(struct pfctl *pf, u_int32_t hostid)
{
	if ((loadopt & PFCTL_FLAG_OPTION) == 0)
		return (0);

	HTONL(hostid);

	pf->hostid = hostid;
	pf->hostid_set = 1;

	if (pf->opts & PF_OPT_VERBOSE)
		printf("set hostid 0x%08x\n", ntohl(hostid));

	return (0);
}
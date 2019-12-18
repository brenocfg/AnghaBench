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
struct rtinfo {int rti_prefixlen; int rti_rtpref; scalar_t__ rti_ltime; int /*<<< orphan*/  rti_prefix; } ;
typedef  int /*<<< orphan*/  ntopbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 scalar_t__ ND6_INFINITE_LIFETIME ; 
 int SSBUFLEN ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,char*) ; 
 char** rtpref_str ; 
 char* sec2str (scalar_t__,char*) ; 

__attribute__((used)) static int
action_show_rtinfo(struct rtinfo *rti)
{
	char ntopbuf[INET6_ADDRSTRLEN];
	char ssbuf[SSBUFLEN];

	printf("\t  %s/%d (pref: %s, ltime: %s)\n",
	    inet_ntop(AF_INET6, &rti->rti_prefix,
		ntopbuf, sizeof(ntopbuf)),
	    rti->rti_prefixlen,
	    rtpref_str[0xff & (rti->rti_rtpref >> 3)],
	    (rti->rti_ltime == ND6_INFINITE_LIFETIME) ?
	    "infinity" : sec2str(rti->rti_ltime, ssbuf));

	return (0);
}
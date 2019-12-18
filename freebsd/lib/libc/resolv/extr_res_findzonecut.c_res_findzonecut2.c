#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union res_sockaddr_union {int dummy; } res_sockaddr_union ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  rrset_ns ;
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  ns_class ;
struct TYPE_7__ {int pfcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ ) ; 
 int NS_MAXDNAME ; 
 int RES_EXHAUSTIVE ; 
 int RES_PRF_ADD ; 
 int RES_PRF_ANS ; 
 int RES_PRF_AUTH ; 
 int RES_PRF_HEAD1 ; 
 int RES_PRF_HEAD2 ; 
 int RES_PRF_HEADX ; 
 int RES_PRF_QUES ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free_nsrrset (int /*<<< orphan*/ *) ; 
 int get_glue (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int get_ns (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int get_soa (TYPE_1__*,char const*,int /*<<< orphan*/ ,int,char*,size_t,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_class (int /*<<< orphan*/ ) ; 
 int satisfy (TYPE_1__*,char*,int /*<<< orphan*/ *,union res_sockaddr_union*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
res_findzonecut2(res_state statp, const char *dname, ns_class class, int opts,
		 char *zname, size_t zsize, union res_sockaddr_union *addrs,
		 int naddrs)
{
	char mname[NS_MAXDNAME];
	u_long save_pfcode;
	rrset_ns nsrrs;
	int n;

	DPRINTF(("START dname='%s' class=%s, zsize=%ld, naddrs=%d",
		 dname, p_class(class), (long)zsize, naddrs));
	save_pfcode = statp->pfcode;
	statp->pfcode |= RES_PRF_HEAD2 | RES_PRF_HEAD1 | RES_PRF_HEADX |
			 RES_PRF_QUES | RES_PRF_ANS |
			 RES_PRF_AUTH | RES_PRF_ADD;
	INIT_LIST(nsrrs);

	DPRINTF(("get the soa, and see if it has enough glue"));
	if ((n = get_soa(statp, dname, class, opts, zname, zsize,
			 mname, sizeof mname, &nsrrs)) < 0 ||
	    ((opts & RES_EXHAUSTIVE) == 0 &&
	     (n = satisfy(statp, mname, &nsrrs, addrs, naddrs)) > 0))
		goto done;

	DPRINTF(("get the ns rrset and see if it has enough glue"));
	if ((n = get_ns(statp, zname, class, opts, &nsrrs)) < 0 ||
	    ((opts & RES_EXHAUSTIVE) == 0 &&
	     (n = satisfy(statp, mname, &nsrrs, addrs, naddrs)) > 0))
		goto done;

	DPRINTF(("get the missing glue and see if it's finally enough"));
	if ((n = get_glue(statp, class, opts, &nsrrs)) >= 0)
		n = satisfy(statp, mname, &nsrrs, addrs, naddrs);

 done:
	DPRINTF(("FINISH n=%d (%s)", n, (n < 0) ? strerror(errno) : "OK"));
	free_nsrrset(&nsrrs);
	statp->pfcode = save_pfcode;
	return (n);
}
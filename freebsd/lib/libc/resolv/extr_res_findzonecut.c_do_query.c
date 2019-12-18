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
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  ns_type ;
typedef  int /*<<< orphan*/  ns_rr ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  scalar_t__ ns_class ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  NS_MAXMSG ; 
 int NS_PACKETSZ ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ns_initparse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ns_msg_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_o_query ; 
 scalar_t__ ns_parserr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ns_rr_class (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_rr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_an ; 
 scalar_t__ ns_t_cname ; 
 scalar_t__ ns_t_dname ; 
 int res_nmkquery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int res_nsend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_query(res_state statp, const char *dname, ns_class class, ns_type qtype,
	 u_char *resp, ns_msg *msg)
{
	u_char req[NS_PACKETSZ];
	int i, n;

	n = res_nmkquery(statp, ns_o_query, dname, class, qtype,
			 NULL, 0, NULL, req, NS_PACKETSZ);
	if (n < 0) {
		DPRINTF(("do_query: res_nmkquery failed"));
		return (-1);
	}
	n = res_nsend(statp, req, n, resp, NS_MAXMSG);
	if (n < 0) {
		DPRINTF(("do_query: res_nsend failed"));
		return (-1);
	}
	if (n == 0) {
		DPRINTF(("do_query: res_nsend returned 0"));
		errno = EMSGSIZE;
		return (-1);
	}
	if (ns_initparse(resp, n, msg) < 0) {
		DPRINTF(("do_query: ns_initparse failed"));
		return (-1);
	}
	n = 0;
	for (i = 0; i < ns_msg_count(*msg, ns_s_an); i++) {
		ns_rr rr;

		if (ns_parserr(msg, ns_s_an, i, &rr) < 0) {
			DPRINTF(("do_query: ns_parserr failed"));
			return (-1);
		}
		n += (ns_rr_class(rr) == class &&
		      (ns_rr_type(rr) == ns_t_cname ||
		       ns_rr_type(rr) == ns_t_dname));
	}
	return (n);
}
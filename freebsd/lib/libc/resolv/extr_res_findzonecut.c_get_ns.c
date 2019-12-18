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
typedef  int /*<<< orphan*/  rrset_ns ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  int /*<<< orphan*/  ns_class ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  NS_MAXMSG ; 
 int do_query (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_an ; 
 int /*<<< orphan*/  ns_t_ns ; 
 int /*<<< orphan*/  p_class (int /*<<< orphan*/ ) ; 
 scalar_t__ save_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_ns(res_state statp, const char *zname, ns_class class, int opts,
      rrset_ns *nsrrsp)
{
	u_char *resp;
	ns_msg msg;
	int n;

	resp = malloc(NS_MAXMSG);
	if (resp == NULL)
		return (-1);

	/* Go and get the NS RRs for this zone. */
	n = do_query(statp, zname, class, ns_t_ns, resp, &msg);
	if (n != 0) {
		DPRINTF(("get_ns: do_query('%s', %s) failed (%d)",
			 zname, p_class(class), n));
		free(resp);
		return (-1);
	}

	/* Remember the NS RRs and associated A RRs that came back. */
	if (save_ns(statp, &msg, ns_s_an, zname, class, opts, nsrrsp) < 0) {
		DPRINTF(("get_ns save_ns('%s', %s) failed",
			 zname, p_class(class)));
		free(resp);
		return (-1);
	}

	free(resp);
	return (0);
}
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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  rrset_ns ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  addrs; } ;
typedef  TYPE_1__ rr_ns ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  int /*<<< orphan*/  ns_class ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_1__* HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_MAXMSG ; 
 int RR_NS_HAVE_V4 ; 
 int RR_NS_HAVE_V6 ; 
 int do_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_nsrr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_an ; 
 int /*<<< orphan*/  ns_t_a ; 
 int /*<<< orphan*/  ns_t_aaaa ; 
 int /*<<< orphan*/  p_class (int /*<<< orphan*/ ) ; 
 scalar_t__ save_a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static int
get_glue(res_state statp, ns_class class, int opts, rrset_ns *nsrrsp) {
	rr_ns *nsrr, *nsrr_n;
	u_char *resp;

	resp = malloc(NS_MAXMSG);
	if (resp == NULL)
		return(-1);

	/* Go and get the A RRs for each empty NS RR on our list. */
	for (nsrr = HEAD(*nsrrsp); nsrr != NULL; nsrr = nsrr_n) {
		ns_msg msg;
		int n;

		nsrr_n = NEXT(nsrr, link);

		if ((nsrr->flags & RR_NS_HAVE_V4) == 0) {
			n = do_query(statp, nsrr->name, class, ns_t_a,
				     resp, &msg);
			if (n < 0) {
				DPRINTF(
				       ("get_glue: do_query('%s', %s') failed",
					nsrr->name, p_class(class)));
				goto cleanup;
			}
			if (n > 0) {
				DPRINTF((
			"get_glue: do_query('%s', %s') CNAME or DNAME found",
					 nsrr->name, p_class(class)));
			}
			if (save_a(statp, &msg, ns_s_an, nsrr->name, class,
				   opts, nsrr) < 0) {
				DPRINTF(("get_glue: save_r('%s', %s) failed",
					 nsrr->name, p_class(class)));
				goto cleanup;
			}
		}

		if ((nsrr->flags & RR_NS_HAVE_V6) == 0) {
			n = do_query(statp, nsrr->name, class, ns_t_aaaa,
				     resp, &msg);
			if (n < 0) {
				DPRINTF(
				       ("get_glue: do_query('%s', %s') failed",
					nsrr->name, p_class(class)));
				goto cleanup;
			}
			if (n > 0) {
				DPRINTF((
			"get_glue: do_query('%s', %s') CNAME or DNAME found",
					 nsrr->name, p_class(class)));
			}
			if (save_a(statp, &msg, ns_s_an, nsrr->name, class,
				   opts, nsrr) < 0) {
				DPRINTF(("get_glue: save_r('%s', %s) failed",
					 nsrr->name, p_class(class)));
				goto cleanup;
			}
		}

		/* If it's still empty, it's just chaff. */
		if (EMPTY(nsrr->addrs)) {
			DPRINTF(("get_glue: removing empty '%s' NS",
				 nsrr->name));
			free_nsrr(nsrrsp, nsrr);
		}
	}
	free(resp);
	return (0);

 cleanup:
	free(resp);
	return (-1);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  rrset_ns ;
struct TYPE_8__ {int /*<<< orphan*/ * name; scalar_t__ flags; int /*<<< orphan*/  addrs; } ;
typedef  TYPE_1__ rr_ns ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  ns_sect ;
typedef  int /*<<< orphan*/  ns_rr ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  scalar_t__ ns_class ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  INIT_LINK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ ) ; 
 int MAXDNAME ; 
 TYPE_1__* find_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  ns_msg_base (int /*<<< orphan*/ ) ; 
 int ns_msg_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_msg_end (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_name_uncompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  ns_o_query ; 
 scalar_t__ ns_parserr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ns_rr_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_rr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ns_rr_rdata (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_rr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_ar ; 
 int ns_samename (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ ns_t_ns ; 
 int /*<<< orphan*/  p_class (scalar_t__) ; 
 int /*<<< orphan*/  p_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ save_a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static int
save_ns(res_state statp, ns_msg *msg, ns_sect sect,
	const char *owner, ns_class class, int opts,
	rrset_ns *nsrrsp)
{
	int i;

	for (i = 0; i < ns_msg_count(*msg, sect); i++) {
		char tname[MAXDNAME];
		const u_char *rdata;
		rr_ns *nsrr;
		ns_rr rr;

		if (ns_parserr(msg, sect, i, &rr) < 0) {
			DPRINTF(("save_ns: ns_parserr(%s, %d) failed",
				 p_section(sect, ns_o_query), i));
			return (-1);
		}
		if (ns_rr_type(rr) != ns_t_ns ||
		    ns_rr_class(rr) != class ||
		    ns_samename(ns_rr_name(rr), owner) != 1)
			continue;
		nsrr = find_ns(nsrrsp, ns_rr_name(rr));
		if (nsrr == NULL) {
			nsrr = malloc(sizeof *nsrr);
			if (nsrr == NULL) {
				DPRINTF(("save_ns: malloc failed"));
				return (-1);
			}
			rdata = ns_rr_rdata(rr);
			if (ns_name_uncompress(ns_msg_base(*msg),
					       ns_msg_end(*msg), rdata,
					       tname, sizeof tname) < 0) {
				DPRINTF(("save_ns: ns_name_uncompress failed")
					);
				free(nsrr);
				return (-1);
			}
			nsrr->name = strdup(tname);
			if (nsrr->name == NULL) {
				DPRINTF(("save_ns: strdup failed"));
				free(nsrr);
				return (-1);
			}
			INIT_LINK(nsrr, link);
			INIT_LIST(nsrr->addrs);
			nsrr->flags = 0;
			APPEND(*nsrrsp, nsrr, link);
		}
		if (save_a(statp, msg, ns_s_ar,
			   nsrr->name, class, opts, nsrr) < 0) {
			DPRINTF(("save_ns: save_r('%s', %s) failed",
				 nsrr->name, p_class(class)));
			return (-1);
		}
	}
	return (0);
}
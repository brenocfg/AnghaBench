#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 char* sldns_wire2str_class (int /*<<< orphan*/ ) ; 
 char* sldns_wire2str_dname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sldns_wire2str_type (int /*<<< orphan*/ ) ; 
 int ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
dump_msg_ref(RES* ssl, struct ub_packed_rrset_key* k)
{
	char* nm, *tp, *cl;
	nm = sldns_wire2str_dname(k->rk.dname, k->rk.dname_len);
	tp = sldns_wire2str_type(ntohs(k->rk.type));
	cl = sldns_wire2str_class(ntohs(k->rk.rrset_class));
	if(!nm || !cl || !tp) {
		free(nm);
		free(tp);
		free(cl);
		return ssl_printf(ssl, "BADREF\n");
	}
	if(!ssl_printf(ssl, "%s %s %s %d\n", nm, cl, tp, (int)k->rk.flags)) {
		free(nm);
		free(tp);
		free(cl);
		return 0;
	}
	free(nm);
	free(tp);
	free(cl);

	return 1;
}
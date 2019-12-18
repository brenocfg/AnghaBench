#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netconfig {scalar_t__ nc_semantics; int /*<<< orphan*/  nc_protofmly; int /*<<< orphan*/  nc_proto; } ;
struct netbuf {int dummy; } ;
typedef  TYPE_1__* rpcb_entry_list_ptr ;
struct TYPE_5__ {scalar_t__ r_nc_semantics; scalar_t__* r_maddr; int /*<<< orphan*/  r_nc_protofmly; int /*<<< orphan*/  r_nc_proto; } ;
typedef  TYPE_2__ rpcb_entry ;
struct TYPE_4__ {TYPE_2__ rpcb_entry_map; struct TYPE_4__* rpcb_entry_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netbuf* uaddr2taddr (struct netconfig const*,scalar_t__*) ; 

__attribute__((used)) static struct netbuf *
got_entry(rpcb_entry_list_ptr relp, const struct netconfig *nconf)
{
	struct netbuf *na = NULL;
	rpcb_entry_list_ptr sp;
	rpcb_entry *rmap;

	for (sp = relp; sp != NULL; sp = sp->rpcb_entry_next) {
		rmap = &sp->rpcb_entry_map;
		if ((strcmp(nconf->nc_proto, rmap->r_nc_proto) == 0) &&
		    (strcmp(nconf->nc_protofmly, rmap->r_nc_protofmly) == 0) &&
		    (nconf->nc_semantics == rmap->r_nc_semantics) &&
		    (rmap->r_maddr != NULL) && (rmap->r_maddr[0] != 0)) {
			na = uaddr2taddr(nconf, rmap->r_maddr);
#ifdef ND_DEBUG
			fprintf(stderr, "\tRemote address is [%s].\n",
				rmap->r_maddr);
			if (!na)
				fprintf(stderr,
				    "\tCouldn't resolve remote address!\n");
#endif
			break;
		}
	}
	return (na);
}
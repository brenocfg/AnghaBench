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
typedef  int /*<<< orphan*/  uint8_t ;
struct query_info {int /*<<< orphan*/ * qname; } ;
struct auth_zone {int dummy; } ;
struct auth_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * dname_get_shared_topdomain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static struct auth_data*
az_find_candidate_ce(struct auth_zone* z, struct query_info* qinfo,
	struct auth_data* n)
{
	uint8_t* nm;
	size_t nmlen;
	if(n) {
		nm = dname_get_shared_topdomain(qinfo->qname, n->name);
	} else {
		nm = qinfo->qname;
	}
	dname_count_size_labels(nm, &nmlen);
	n = az_find_name(z, nm, nmlen);
	/* delete labels and go up on name */
	while(!n) {
		if(dname_is_root(nm))
			return NULL; /* cannot go up */
		dname_remove_label(&nm, &nmlen);
		n = az_find_name(z, nm, nmlen);
	}
	return n;
}
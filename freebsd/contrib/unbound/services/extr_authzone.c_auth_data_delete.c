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
struct auth_rrset {struct auth_rrset* next; } ;
struct auth_data {struct auth_data* name; struct auth_rrset* rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_rrset_delete (struct auth_rrset*) ; 
 int /*<<< orphan*/  free (struct auth_data*) ; 

__attribute__((used)) static void
auth_data_delete(struct auth_data* n)
{
	struct auth_rrset* p, *np;
	if(!n) return;
	p = n->rrsets;
	while(p) {
		np = p->next;
		auth_rrset_delete(p);
		p = np;
	}
	free(n->name);
	free(n);
}
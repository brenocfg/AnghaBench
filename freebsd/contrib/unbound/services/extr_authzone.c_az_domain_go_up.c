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
struct auth_zone {int dummy; } ;
struct auth_data {size_t namelen; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static struct auth_data*
az_domain_go_up(struct auth_zone* z, struct auth_data* n)
{
	uint8_t* nm = n->name;
	size_t nmlen = n->namelen;
	while(!dname_is_root(nm)) {
		dname_remove_label(&nm, &nmlen);
		if((n=az_find_name(z, nm, nmlen)) != NULL)
			return n;
	}
	return NULL;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct auth_zone {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct auth_data* key; } ;
struct auth_data {size_t namelen; struct auth_data* name; TYPE_1__ node; int /*<<< orphan*/  namelabs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct auth_data*) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 scalar_t__ malloc (int) ; 
 struct auth_data* memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (struct auth_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static struct auth_data*
az_domain_create(struct auth_zone* z, uint8_t* nm, size_t nmlen)
{
	struct auth_data* n = (struct auth_data*)malloc(sizeof(*n));
	if(!n) return NULL;
	memset(n, 0, sizeof(*n));
	n->node.key = n;
	n->name = memdup(nm, nmlen);
	if(!n->name) {
		free(n);
		return NULL;
	}
	n->namelen = nmlen;
	n->namelabs = dname_count_labels(nm);
	if(!rbtree_insert(&z->data, &n->node)) {
		log_warn("duplicate auth domain name");
		free(n->name);
		free(n);
		return NULL;
	}
	return n;
}
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
struct local_zone {int namelabs; int /*<<< orphan*/  data; int /*<<< orphan*/  region; } ;
struct TYPE_2__ {struct local_data* key; } ;
struct local_data {size_t namelen; int namelabs; TYPE_1__ node; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 struct local_data* lz_find_node (struct local_zone*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  regional_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ regional_alloc_zero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lz_find_create_node(struct local_zone* z, uint8_t* nm, size_t nmlen, 
	int nmlabs, struct local_data** res)
{
	struct local_data* ld = lz_find_node(z, nm, nmlen, nmlabs);
	if(!ld) {
		/* create a domain name to store rr. */
		ld = (struct local_data*)regional_alloc_zero(z->region,
			sizeof(*ld));
		if(!ld) {
			log_err("out of memory adding local data");
			return 0;
		}
		ld->node.key = ld;
		ld->name = regional_alloc_init(z->region, nm, nmlen);
		if(!ld->name) {
			log_err("out of memory");
			return 0;
		}
		ld->namelen = nmlen;
		ld->namelabs = nmlabs;
		if(!rbtree_insert(&z->data, &ld->node)) {
			log_assert(0); /* duplicate name */
		}
		/* see if empty nonterminals need to be created */
		if(nmlabs > z->namelabs) {
			dname_remove_label(&nm, &nmlen);
			if(!lz_find_create_node(z, nm, nmlen, nmlabs-1, res))
				return 0;
		}
	}
	*res = ld;
	return 1;
}
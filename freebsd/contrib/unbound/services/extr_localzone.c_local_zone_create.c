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
typedef  int /*<<< orphan*/  uint16_t ;
struct regional {int dummy; } ;
struct TYPE_2__ {struct local_zone* key; } ;
struct local_zone {int type; size_t namelen; int namelabs; int /*<<< orphan*/  parent; int /*<<< orphan*/  lock; int /*<<< orphan*/  data; int /*<<< orphan*/  region; int /*<<< orphan*/ * name; int /*<<< orphan*/  dclass; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct local_zone*) ; 
 int /*<<< orphan*/  local_data_cmp ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regional_create_custom (int) ; 

__attribute__((used)) static struct local_zone*
local_zone_create(uint8_t* nm, size_t len, int labs, 
	enum localzone_type t, uint16_t dclass)
{
	struct local_zone* z = (struct local_zone*)calloc(1, sizeof(*z));
	if(!z) {
		return NULL;
	}
	z->node.key = z;
	z->dclass = dclass;
	z->type = t;
	z->name = nm;
	z->namelen = len;
	z->namelabs = labs;
	lock_rw_init(&z->lock);
	z->region = regional_create_custom(sizeof(struct regional));
	if(!z->region) {
		free(z);
		return NULL;
	}
	rbtree_init(&z->data, &local_data_cmp);
	lock_protect(&z->lock, &z->parent, sizeof(*z)-sizeof(rbnode_type));
	/* also the zones->lock protects node, parent, name*, class */
	return z;
}
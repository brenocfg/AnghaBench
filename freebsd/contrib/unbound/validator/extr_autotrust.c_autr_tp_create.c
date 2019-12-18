#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct val_anchors {int /*<<< orphan*/  lock; int /*<<< orphan*/ * tree; TYPE_1__* autr; } ;
struct TYPE_4__ {struct trust_anchor* key; } ;
struct trust_anchor {size_t namelen; struct trust_anchor* autr; int /*<<< orphan*/  lock; struct trust_anchor* name; TYPE_2__ pnode; TYPE_2__ node; int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelabs; } ;
struct autr_point_data {size_t namelen; struct autr_point_data* autr; int /*<<< orphan*/  lock; struct autr_point_data* name; TYPE_2__ pnode; TYPE_2__ node; int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelabs; } ;
struct TYPE_3__ {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_count_labels (struct trust_anchor*) ; 
 int /*<<< orphan*/  free (struct trust_anchor*) ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,struct trust_anchor*,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 struct trust_anchor* memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct trust_anchor*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static struct trust_anchor*
autr_tp_create(struct val_anchors* anchors, uint8_t* own, size_t own_len,
	uint16_t dc)
{
	struct trust_anchor* tp = (struct trust_anchor*)calloc(1, sizeof(*tp));
	if(!tp) return NULL;
	tp->name = memdup(own, own_len);
	if(!tp->name) {
		free(tp);
		return NULL;
	}
	tp->namelen = own_len;
	tp->namelabs = dname_count_labels(tp->name);
	tp->node.key = tp;
	tp->dclass = dc;
	tp->autr = (struct autr_point_data*)calloc(1, sizeof(*tp->autr));
	if(!tp->autr) {
		free(tp->name);
		free(tp);
		return NULL;
	}
	tp->autr->pnode.key = tp;

	lock_basic_lock(&anchors->lock);
	if(!rbtree_insert(anchors->tree, &tp->node)) {
		lock_basic_unlock(&anchors->lock);
		log_err("trust anchor presented twice");
		free(tp->name);
		free(tp->autr);
		free(tp);
		return NULL;
	}
	if(!rbtree_insert(&anchors->autr->probe, &tp->autr->pnode)) {
		(void)rbtree_delete(anchors->tree, tp);
		lock_basic_unlock(&anchors->lock);
		log_err("trust anchor in probetree twice");
		free(tp->name);
		free(tp->autr);
		free(tp);
		return NULL;
	}
	lock_basic_unlock(&anchors->lock);
	lock_basic_init(&tp->lock);
	lock_protect(&tp->lock, tp, sizeof(*tp));
	lock_protect(&tp->lock, tp->autr, sizeof(*tp->autr));
	return tp;
}
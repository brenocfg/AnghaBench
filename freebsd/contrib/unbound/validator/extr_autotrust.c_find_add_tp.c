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
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; int /*<<< orphan*/  autr; } ;

/* Variables and functions */
 struct trust_anchor* anchor_find (struct val_anchors*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 struct trust_anchor* autr_tp_create (struct val_anchors*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static struct trust_anchor*
find_add_tp(struct val_anchors* anchors, uint8_t* rr, size_t rr_len,
	size_t dname_len)
{
	struct trust_anchor* tp;
	tp = anchor_find(anchors, rr, dname_count_labels(rr), dname_len,
		sldns_wirerr_get_class(rr, rr_len, dname_len));
	if(tp) {
		if(!tp->autr) {
			log_err("anchor cannot be with and without autotrust");
			lock_basic_unlock(&tp->lock);
			return NULL;
		}
		return tp;
	}
	tp = autr_tp_create(anchors, rr, dname_len, sldns_wirerr_get_class(rr,
		rr_len, dname_len));
	if(!tp)	
		return NULL;
	lock_basic_lock(&tp->lock);
	return tp;
}
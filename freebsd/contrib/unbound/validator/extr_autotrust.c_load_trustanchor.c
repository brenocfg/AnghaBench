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
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; TYPE_1__* autr; } ;
struct autr_ta {int dummy; } ;
struct TYPE_2__ {scalar_t__ file; } ;

/* Variables and functions */
 struct autr_ta* add_trustanchor_frm_str (struct val_anchors*,char*,struct trust_anchor**,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  parse_comments (char*,struct autr_ta*) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static struct trust_anchor*
load_trustanchor(struct val_anchors* anchors, char* str, const char* fname,
	uint8_t* origin, size_t origin_len, uint8_t** prev, size_t* prev_len,
	int* skip)
{
	struct autr_ta* ta = NULL;
	struct trust_anchor* tp = NULL;

	ta = add_trustanchor_frm_str(anchors, str, &tp, origin, origin_len,
		prev, prev_len, skip);
	if(!ta)
		return NULL;
	lock_basic_lock(&tp->lock);
	if(!parse_comments(str, ta)) {
		lock_basic_unlock(&tp->lock);
		return NULL;
	}
	if(!tp->autr->file) {
		tp->autr->file = strdup(fname);
		if(!tp->autr->file) {
			lock_basic_unlock(&tp->lock);
			log_err("malloc failure");
			return NULL;
		}
	}
	lock_basic_unlock(&tp->lock);
        return tp;
}
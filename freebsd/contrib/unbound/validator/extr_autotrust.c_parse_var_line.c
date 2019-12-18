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
typedef  scalar_t__ uint8_t ;
typedef  void* time_t ;
struct val_anchors {int /*<<< orphan*/  lock; TYPE_1__* autr; } ;
struct trust_anchor {int /*<<< orphan*/  lock; TYPE_2__* autr; } ;
struct TYPE_4__ {void* retry_time; void* query_interval; scalar_t__ query_failed; int /*<<< orphan*/  pnode; void* next_probe_time; void* last_success; void* last_queried; } ;
struct TYPE_3__ {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 struct trust_anchor* parse_id (struct val_anchors*,char*) ; 
 scalar_t__ parse_int (char*,int*) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct trust_anchor*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
parse_var_line(char* line, struct val_anchors* anchors, 
	struct trust_anchor** anchor)
{
	struct trust_anchor* tp = *anchor;
	int r = 0;
	if(strncmp(line, ";;id: ", 6) == 0) {
		*anchor = parse_id(anchors, line+6);
		if(!*anchor) return -1;
		else return 1;
	} else if(strncmp(line, ";;REVOKED", 9) == 0) {
		if(tp) {
			log_err("REVOKED statement must be at start of file");
			return -1;
		}
		return 2;
	} else if(strncmp(line, ";;last_queried: ", 16) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&tp->lock);
		tp->autr->last_queried = (time_t)parse_int(line+16, &r);
		lock_basic_unlock(&tp->lock);
	} else if(strncmp(line, ";;last_success: ", 16) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&tp->lock);
		tp->autr->last_success = (time_t)parse_int(line+16, &r);
		lock_basic_unlock(&tp->lock);
	} else if(strncmp(line, ";;next_probe_time: ", 19) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&anchors->lock);
		lock_basic_lock(&tp->lock);
		(void)rbtree_delete(&anchors->autr->probe, tp);
		tp->autr->next_probe_time = (time_t)parse_int(line+19, &r);
		(void)rbtree_insert(&anchors->autr->probe, &tp->autr->pnode);
		lock_basic_unlock(&tp->lock);
		lock_basic_unlock(&anchors->lock);
	} else if(strncmp(line, ";;query_failed: ", 16) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&tp->lock);
		tp->autr->query_failed = (uint8_t)parse_int(line+16, &r);
		lock_basic_unlock(&tp->lock);
	} else if(strncmp(line, ";;query_interval: ", 18) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&tp->lock);
		tp->autr->query_interval = (time_t)parse_int(line+18, &r);
		lock_basic_unlock(&tp->lock);
	} else if(strncmp(line, ";;retry_time: ", 14) == 0) {
		if(!tp) return -1;
		lock_basic_lock(&tp->lock);
		tp->autr->retry_time = (time_t)parse_int(line+14, &r);
		lock_basic_unlock(&tp->lock);
	}
	return r;
}
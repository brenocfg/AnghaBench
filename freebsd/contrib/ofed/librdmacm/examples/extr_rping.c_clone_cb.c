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
struct rping_cb {TYPE_1__* child_cm_id; } ;
struct TYPE_2__ {struct rping_cb* context; } ;

/* Variables and functions */
 struct rping_cb* malloc (int) ; 
 int /*<<< orphan*/  memset (struct rping_cb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct rping_cb *clone_cb(struct rping_cb *listening_cb)
{
	struct rping_cb *cb = malloc(sizeof *cb);
	if (!cb)
		return NULL;
	memset(cb, 0, sizeof *cb);
	*cb = *listening_cb;
	cb->child_cm_id->context = cb;
	return cb;
}
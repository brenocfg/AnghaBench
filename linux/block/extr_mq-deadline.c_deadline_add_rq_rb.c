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
struct request {int dummy; } ;
struct rb_root {int dummy; } ;
struct deadline_data {int dummy; } ;

/* Variables and functions */
 struct rb_root* deadline_rb_root (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rb_add (struct rb_root*,struct request*) ; 

__attribute__((used)) static void
deadline_add_rq_rb(struct deadline_data *dd, struct request *rq)
{
	struct rb_root *root = deadline_rb_root(dd, rq);

	elv_rb_add(root, rq);
}
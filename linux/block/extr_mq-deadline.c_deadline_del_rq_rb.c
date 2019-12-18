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
struct deadline_data {struct request** next_rq; } ;

/* Variables and functions */
 struct request* deadline_latter_request (struct request*) ; 
 int /*<<< orphan*/  deadline_rb_root (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ ,struct request*) ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static inline void
deadline_del_rq_rb(struct deadline_data *dd, struct request *rq)
{
	const int data_dir = rq_data_dir(rq);

	if (dd->next_rq[data_dir] == rq)
		dd->next_rq[data_dir] = deadline_latter_request(rq);

	elv_rb_del(deadline_rb_root(dd, rq), rq);
}
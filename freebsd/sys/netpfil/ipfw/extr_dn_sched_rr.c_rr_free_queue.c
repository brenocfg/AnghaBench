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
struct rr_si {int dummy; } ;
struct rr_queue {int status; } ;
struct dn_queue {scalar_t__ _si; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*) ; 
 int /*<<< orphan*/  remove_queue_q (struct rr_queue*,struct rr_si*) ; 

__attribute__((used)) static int
rr_free_queue(struct dn_queue *_q)
{
	struct rr_queue *q = (struct rr_queue *)_q;

	ND("called");
	if (q->status == 1) {
		struct rr_si *si = (struct rr_si *)(_q->_si + 1);
		remove_queue_q(q, si);
	}
	return 0;
}
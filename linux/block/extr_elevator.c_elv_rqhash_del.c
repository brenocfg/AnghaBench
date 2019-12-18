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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 scalar_t__ ELV_ON_HASH (struct request*) ; 
 int /*<<< orphan*/  __elv_rqhash_del (struct request*) ; 

void elv_rqhash_del(struct request_queue *q, struct request *rq)
{
	if (ELV_ON_HASH(rq))
		__elv_rqhash_del(rq);
}
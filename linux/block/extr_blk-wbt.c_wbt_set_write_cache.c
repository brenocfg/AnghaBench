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
struct rq_qos {int dummy; } ;
struct request_queue {int dummy; } ;
struct TYPE_2__ {int wc; } ;

/* Variables and functions */
 TYPE_1__* RQWB (struct rq_qos*) ; 
 struct rq_qos* wbt_rq_qos (struct request_queue*) ; 

void wbt_set_write_cache(struct request_queue *q, bool write_cache_on)
{
	struct rq_qos *rqos = wbt_rq_qos(q);
	if (rqos)
		RQWB(rqos)->wc = write_cache_on;
}
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
struct kyber_queue_data {int /*<<< orphan*/  q; TYPE_2__* domain_tokens; } ;
struct TYPE_3__ {unsigned int depth; } ;
struct TYPE_4__ {TYPE_1__ sb; } ;

/* Variables and functions */
 unsigned int clamp (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kyber_depth ; 
 int /*<<< orphan*/ * kyber_domain_names ; 
 int /*<<< orphan*/  sbitmap_queue_resize (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  trace_kyber_adjust (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void kyber_resize_domain(struct kyber_queue_data *kqd,
				unsigned int sched_domain, unsigned int depth)
{
	depth = clamp(depth, 1U, kyber_depth[sched_domain]);
	if (depth != kqd->domain_tokens[sched_domain].sb.depth) {
		sbitmap_queue_resize(&kqd->domain_tokens[sched_domain], depth);
		trace_kyber_adjust(kqd->q, kyber_domain_names[sched_domain],
				   depth);
	}
}
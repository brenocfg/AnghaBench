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
typedef  scalar_t__ uint64_t ;
struct opal_sg_list {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct opal_sg_list* __va (scalar_t__) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct opal_sg_list*) ; 

void opal_free_sg_list(struct opal_sg_list *sg)
{
	while (sg) {
		uint64_t next = be64_to_cpu(sg->next);

		kfree(sg);

		if (next)
			sg = __va(next);
		else
			sg = NULL;
	}
}
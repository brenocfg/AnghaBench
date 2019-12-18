#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ccp_sg_workarea {unsigned int bytes_left; scalar_t__ sg_used; TYPE_1__* sg; } ;
struct TYPE_3__ {scalar_t__ length; } ;

/* Variables and functions */
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 TYPE_1__* sg_next (TYPE_1__*) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static void ccp_update_sg_workarea(struct ccp_sg_workarea *wa, unsigned int len)
{
	unsigned int nbytes = min_t(u64, len, wa->bytes_left);

	if (!wa->sg)
		return;

	wa->sg_used += nbytes;
	wa->bytes_left -= nbytes;
	if (wa->sg_used == wa->sg->length) {
		wa->sg = sg_next(wa->sg);
		wa->sg_used = 0;
	}
}
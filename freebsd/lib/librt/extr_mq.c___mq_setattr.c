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
struct mq_attr {int dummy; } ;
typedef  TYPE_1__* mqd_t ;
struct TYPE_3__ {int /*<<< orphan*/  oshandle; } ;

/* Variables and functions */
 int __sys_kmq_setattr (int /*<<< orphan*/ ,struct mq_attr const*,struct mq_attr*) ; 

int
__mq_setattr(mqd_t mqd, const struct mq_attr *newattr, struct mq_attr *oldattr)
{

	return __sys_kmq_setattr(mqd->oshandle, newattr, oldattr);
}
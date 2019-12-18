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
struct TYPE_3__ {int /*<<< orphan*/  (* seed ) (void const*,int) ;} ;
typedef  TYPE_1__ RAND_METHOD ;

/* Variables and functions */
 TYPE_1__* RAND_get_rand_method () ; 
 int /*<<< orphan*/  stub1 (void const*,int) ; 

void RAND_seed(const void *buf, int num)
{
    const RAND_METHOD *meth = RAND_get_rand_method();

    if (meth->seed != NULL)
        meth->seed(buf, num);
}
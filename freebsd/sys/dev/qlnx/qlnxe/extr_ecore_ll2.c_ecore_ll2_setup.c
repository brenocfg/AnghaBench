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
struct ecore_hwfn {TYPE_1__* p_ll2_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ECORE_MAX_NUM_OF_LL2_CONNECTIONS ; 
 int /*<<< orphan*/  OSAL_MUTEX_INIT (int /*<<< orphan*/ *) ; 

void ecore_ll2_setup(struct ecore_hwfn *p_hwfn)
{
	int  i;

	for (i = 0; i < ECORE_MAX_NUM_OF_LL2_CONNECTIONS; i++)
		OSAL_MUTEX_INIT(&p_hwfn->p_ll2_info[i].mutex);
}
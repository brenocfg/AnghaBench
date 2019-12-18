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
struct TYPE_2__ {void* b_valid; void* init_val; } ;
struct ecore_hwfn {TYPE_1__ rt_data; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,void*) ; 
 void* OSAL_NULL ; 

void ecore_init_free(struct ecore_hwfn *p_hwfn)
{
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->rt_data.init_val);
	p_hwfn->rt_data.init_val = OSAL_NULL;
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->rt_data.b_valid);
	p_hwfn->rt_data.b_valid = OSAL_NULL;
}
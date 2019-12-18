#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* b_cont; scalar_t__ b_rptr; scalar_t__ b_wptr; } ;
typedef  TYPE_1__ mblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  freeb (TYPE_1__*) ; 

__attribute__((used)) static unsigned long
rdchar(
       register mblk_t **mp
       )
{
	while (*mp != (mblk_t *)NULL)
	{
		if ((*mp)->b_wptr - (*mp)->b_rptr)
		{
			return (unsigned long)(*(unsigned char *)((*mp)->b_rptr++));
		}
		else
		{
			register mblk_t *mmp = *mp;

			*mp = (*mp)->b_cont;
			freeb(mmp);
		}
	}
	return (unsigned)~0;
}
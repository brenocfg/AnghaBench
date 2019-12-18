#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* wd_loadav; } ;
struct TYPE_5__ {TYPE_1__ hs_wd; } ;

/* Variables and functions */
 TYPE_2__* HS (void const*) ; 
 scalar_t__ ISDOWN (TYPE_2__*) ; 
 int rflg ; 
 int tcmp (void const*,void const*) ; 

__attribute__((used)) static int
lcmp(const void *a1, const void *a2)
{
	if (ISDOWN(HS(a1)))
		if (ISDOWN(HS(a2)))
			return (tcmp(a1, a2));
		else
			return (rflg);
	else if (ISDOWN(HS(a2)))
		return (-rflg);
	else
		return (rflg *
		   (HS(a2)->hs_wd.wd_loadav[0] - HS(a1)->hs_wd.wd_loadav[0]));
}
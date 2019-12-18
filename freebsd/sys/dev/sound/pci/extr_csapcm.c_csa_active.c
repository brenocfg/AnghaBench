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
struct csa_info {int active; TYPE_1__* card; } ;
struct TYPE_2__ {int (* active ) (int) ;} ;

/* Variables and functions */
 int stub1 (int) ; 

__attribute__((used)) static int
csa_active(struct csa_info *csa, int run)
{
	int old;

	old = csa->active;
	csa->active += run;

	if ((csa->active > 1) || (csa->active < -1))
		csa->active = 0;
	if (csa->card->active)
		return (csa->card->active(!(csa->active && old)));

	return 0;
}
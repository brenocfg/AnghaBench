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
struct consdev {int /*<<< orphan*/  cn_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int OF_finddevice (char*) ; 

__attribute__((used)) static void
mambo_cnprobe(struct consdev *cp)
{
	if (OF_finddevice("/mambo") == -1) {
		cp->cn_pri = CN_DEAD;
		return;
	}

	cp->cn_pri = CN_NORMAL;
}
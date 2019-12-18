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
struct speedtab {int speed; int uxname; } ;

/* Variables and functions */
 int B230400 ; 
 int B300 ; 
 struct speedtab* speedtab ; 

int
speed(int val)
{
	struct speedtab *sp;

	if (val <= B230400)
		return (val);

	for (sp = speedtab; sp->speed; sp++)
		if (sp->speed == val)
			return (sp->uxname);

	return (B300);		/* default in impossible cases */
}
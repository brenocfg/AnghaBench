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

/* Variables and functions */
 scalar_t__ delm (int*) ; 
 int /*<<< orphan*/ * dot ; 
 int /*<<< orphan*/ * message ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  touch (int /*<<< orphan*/ *) ; 
 int type (int*) ; 

int
deltype(void *v)
{
	int *msgvec = v;
	int list[2];
	int lastdot;

	lastdot = dot - &message[0] + 1;
	if (delm(msgvec) >= 0) {
		list[0] = dot - &message[0] + 1;
		if (list[0] > lastdot) {
			touch(dot);
			list[1] = 0;
			return (type(list));
		}
		printf("At EOF\n");
	} else
		printf("No more messages\n");
	return (0);
}
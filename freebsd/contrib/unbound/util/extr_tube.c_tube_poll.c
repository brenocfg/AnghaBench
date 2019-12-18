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
typedef  int /*<<< orphan*/  t ;
struct tube {int /*<<< orphan*/  sr; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int pollit (int /*<<< orphan*/ ,struct timeval*) ; 

int tube_poll(struct tube* tube)
{
	struct timeval t;
	memset(&t, 0, sizeof(t));
	return pollit(tube->sr, &t);
}
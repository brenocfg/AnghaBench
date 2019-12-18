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
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int fread (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ tail ; 

int
fread_tail(void *buf, int size, int num)
{
	int i;

	while ((i = fread(buf, size, num, stdin)) == 0 && tail) {
		sleep(1);
		clearerr(stdin);
	}
	return (i);
}
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
struct rtld_lock {int dummy; } ;

/* Variables and functions */
 int busy_places ; 
 struct rtld_lock* lock_place ; 

__attribute__((used)) static void
_thr_rtld_lock_destroy(void *lock)
{
	int locki;
	size_t i;

	locki = (struct rtld_lock *)lock - &lock_place[0];
	for (i = 0; i < sizeof(struct rtld_lock); ++i)
		((char *)lock)[i] = 0;
	busy_places &= ~(1 << locki);
}
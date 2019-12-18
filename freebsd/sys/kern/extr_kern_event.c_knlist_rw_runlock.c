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
struct rwlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_runlock (struct rwlock*) ; 

__attribute__((used)) static void
knlist_rw_runlock(void *arg)
{

	rw_runlock((struct rwlock *)arg);
}
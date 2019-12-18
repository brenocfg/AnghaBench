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
struct rtentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_UNLOCK_COND (struct rtentry*) ; 

__attribute__((used)) static void
rtentry_dtor(void *mem, int size, void *arg)
{
	struct rtentry *rt = mem;

	RT_UNLOCK_COND(rt);
}
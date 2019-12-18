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
struct rtentry {int /*<<< orphan*/ * rt_pksent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RT_LOCK_INIT (struct rtentry*) ; 
 int /*<<< orphan*/ * counter_u64_alloc (int) ; 

__attribute__((used)) static int
rtentry_zinit(void *mem, int size, int how)
{
	struct rtentry *rt = mem;

	rt->rt_pksent = counter_u64_alloc(how);
	if (rt->rt_pksent == NULL)
		return (ENOMEM);

	RT_LOCK_INIT(rt);

	return (0);
}
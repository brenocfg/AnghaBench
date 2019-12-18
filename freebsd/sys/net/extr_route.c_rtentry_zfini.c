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
struct rtentry {int /*<<< orphan*/  rt_pksent; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_LOCK_DESTROY (struct rtentry*) ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtentry_zfini(void *mem, int size)
{
	struct rtentry *rt = mem;

	RT_LOCK_DESTROY(rt);
	counter_u64_free(rt->rt_pksent);
}
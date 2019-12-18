#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int counter; } ;
typedef  TYPE_1__ atomic_t ;

/* Variables and functions */
 int atomic_cmpxchg (TYPE_1__*,int,int const) ; 

__attribute__((used)) static uint8_t
linux_update_state(atomic_t *v, const uint8_t *pstate)
{
	int c, old;

	c = v->counter;

	while ((old = atomic_cmpxchg(v, c, pstate[c])) != c)
		c = old;

	return (c);
}
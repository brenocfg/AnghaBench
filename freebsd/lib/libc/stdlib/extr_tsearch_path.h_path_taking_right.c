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
struct path {uintptr_t* steps; size_t nsteps; } ;

/* Variables and functions */
 size_t STEPS_BIT ; 

__attribute__((used)) static inline void
path_taking_right(struct path *p)
{

	p->steps[p->nsteps / STEPS_BIT] &=
	    ~((uintptr_t)1 << (p->nsteps % STEPS_BIT));
	++p->nsteps;
}
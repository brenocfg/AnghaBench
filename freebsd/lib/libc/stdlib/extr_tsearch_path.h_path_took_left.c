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
struct path {int* steps; } ;

/* Variables and functions */
 int STEPS_BIT ; 

__attribute__((used)) static inline bool
path_took_left(struct path *p)
{
	bool result;

	result = p->steps[0] & 0x1;
	p->steps[0] = (p->steps[0] >> 1) | (p->steps[1] << (STEPS_BIT - 1));
	p->steps[1] >>= 1;
	return (result);
}
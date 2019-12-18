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
struct cdeque {int cap_mask; int /*<<< orphan*/ * arr; } ;

/* Variables and functions */
 int CDE_ALLOC ; 
 int CDE_OK ; 
 int CDE_PARAM ; 
 int /*<<< orphan*/  cdeque_clear (struct cdeque*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static int cdeque_init(struct cdeque* d, int max_capacity_power_of_2) {
	if(d == NULL || max_capacity_power_of_2 == 0)
		return CDE_PARAM;

	d->cap_mask = max_capacity_power_of_2 - 1;
	d->arr = NULL;

	if((max_capacity_power_of_2 & d->cap_mask) > 0)
		return CDE_PARAM;

	cdeque_clear(d);
	d->arr = malloc(sizeof(void*) * max_capacity_power_of_2);

	return d->arr ? CDE_OK : CDE_ALLOC;
}
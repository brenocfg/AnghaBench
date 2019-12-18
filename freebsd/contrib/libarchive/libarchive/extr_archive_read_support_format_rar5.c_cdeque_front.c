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
struct cdeque {scalar_t__ size; } ;

/* Variables and functions */
 int CDE_OK ; 
 int CDE_OUT_OF_BOUNDS ; 
 int /*<<< orphan*/  cdeque_front_fast (struct cdeque*,void**) ; 

__attribute__((used)) static int cdeque_front(struct cdeque* d, void** value) {
	if(d->size > 0) {
		cdeque_front_fast(d, value);
		return CDE_OK;
	} else
		return CDE_OUT_OF_BOUNDS;
}
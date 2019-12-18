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
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int kobj_init1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
kobj_init(kobj_t obj, kobj_class_t cls)
{
	int error;

	error = kobj_init1(obj, cls, M_NOWAIT);
	if (error != 0)
		panic("kobj_init1 failed: error %d", error);
}
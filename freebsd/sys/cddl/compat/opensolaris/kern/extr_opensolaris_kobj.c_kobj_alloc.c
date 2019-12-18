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

/* Variables and functions */
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int KM_NOWAIT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 void* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 

void *
kobj_alloc(size_t size, int flag)
{

	return (kmem_alloc(size, (flag & KM_NOWAIT) ? KM_NOSLEEP : KM_SLEEP));
}
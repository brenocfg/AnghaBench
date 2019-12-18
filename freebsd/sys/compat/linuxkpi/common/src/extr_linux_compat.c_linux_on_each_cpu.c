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
 int /*<<< orphan*/  smp_no_rendezvous_barrier ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ,void*) ; 

int
linux_on_each_cpu(void callback(void *), void *data)
{

	smp_rendezvous(smp_no_rendezvous_barrier, callback,
	    smp_no_rendezvous_barrier, data);
	return (0);
}
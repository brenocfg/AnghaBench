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
struct mem_range_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,void (*) (void*),int /*<<< orphan*/ *,struct mem_range_softc*) ; 
 scalar_t__ x86_mrAPinit ; 

__attribute__((used)) static void
x86_mrreinit(struct mem_range_softc *sc)
{

	smp_rendezvous(NULL, (void (*)(void *))x86_mrAPinit, NULL, sc);
}
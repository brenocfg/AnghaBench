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
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mem_range_softc*) ; 
 int /*<<< orphan*/  x86_mrstoreone ; 

__attribute__((used)) static void
x86_mrstore(struct mem_range_softc *sc)
{

	smp_rendezvous(NULL, x86_mrstoreone, NULL, sc);
}
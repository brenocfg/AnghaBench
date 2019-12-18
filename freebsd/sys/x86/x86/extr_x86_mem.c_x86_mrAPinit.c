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
 int /*<<< orphan*/  MSR_MTRRdefType ; 
 int /*<<< orphan*/  mtrrdef ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_mrstoreone (struct mem_range_softc*) ; 

__attribute__((used)) static void
x86_mrAPinit(struct mem_range_softc *sc)
{

	x86_mrstoreone(sc);
	wrmsr(MSR_MTRRdefType, mtrrdef);
}
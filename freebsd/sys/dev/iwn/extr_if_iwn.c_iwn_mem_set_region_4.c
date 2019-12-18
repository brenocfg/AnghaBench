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
typedef  int uint32_t ;
struct iwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwn_mem_write (struct iwn_softc*,int,int) ; 

__attribute__((used)) static __inline void
iwn_mem_set_region_4(struct iwn_softc *sc, uint32_t addr, uint32_t val,
    int count)
{
	for (; count > 0; count--, addr += 4)
		iwn_mem_write(sc, addr, val);
}
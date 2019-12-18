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

/* Variables and functions */
 int pl310_read4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pl310_softc ; 

__attribute__((used)) static __inline void
pl310_wait_background_op(uint32_t off, uint32_t mask)
{

	while (pl310_read4(pl310_softc, off) & mask)
		continue;
}
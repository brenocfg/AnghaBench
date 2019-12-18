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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct a10_timer_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNT64_CTRL_REG ; 
 int CNT64_CTRL_RL_EN ; 
 int /*<<< orphan*/  CNT64_HI_REG ; 
 int /*<<< orphan*/  CNT64_LO_REG ; 
 int timer_read_4 (struct a10_timer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_write_4 (struct a10_timer_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint64_t
timer_read_counter64(struct a10_timer_softc *sc)
{
	uint32_t lo, hi;

	/* Latch counter, wait for it to be ready to read. */
	timer_write_4(sc, CNT64_CTRL_REG, CNT64_CTRL_RL_EN);
	while (timer_read_4(sc, CNT64_CTRL_REG) & CNT64_CTRL_RL_EN)
		continue;

	hi = timer_read_4(sc, CNT64_HI_REG);
	lo = timer_read_4(sc, CNT64_LO_REG);

	return (((uint64_t)hi << 32) | lo);
}
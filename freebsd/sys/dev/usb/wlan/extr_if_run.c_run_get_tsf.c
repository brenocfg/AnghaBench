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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_TSF_TIMER_DW0 ; 
 int /*<<< orphan*/  run_read_region_1 (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
run_get_tsf(struct run_softc *sc, uint64_t *buf)
{
	run_read_region_1(sc, RT2860_TSF_TIMER_DW0, (uint8_t *)buf,
	    sizeof(*buf));
}
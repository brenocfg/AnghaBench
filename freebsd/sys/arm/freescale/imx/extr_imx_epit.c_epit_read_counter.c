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
typedef  scalar_t__ u_int ;
struct epit_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIT_CNR ; 
 scalar_t__ RD4 (struct epit_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
epit_read_counter(struct epit_softc *sc)
{

	/*
	 * Hardware is a downcounter, adjust to look like it counts up for use
	 * with timecounter and DELAY.
	 */
	return (0xffffffff - RD4(sc, EPIT_CNR));
}
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
struct rsu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92S_LEDCFG ; 
 int rsu_read_1 (struct rsu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_write_1 (struct rsu_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rsu_set_led(struct rsu_softc *sc, int on)
{
	rsu_write_1(sc, R92S_LEDCFG,
	    (rsu_read_1(sc, R92S_LEDCFG) & 0xf0) | (!on << 3));
}
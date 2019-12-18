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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_calib_cb ; 
 int /*<<< orphan*/  rtwn_cmd_sleepable (struct rtwn_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rtwn_calib_to(void *arg)
{
	struct rtwn_softc *sc = arg;

	/* Do it in a process context. */
	rtwn_cmd_sleepable(sc, NULL, 0, rtwn_calib_cb);
}
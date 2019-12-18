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
 int /*<<< orphan*/  r92c_handle_c2h_task ; 
 int /*<<< orphan*/  rtwn_cmd_sleepable (struct rtwn_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r92c_handle_c2h_report(void *arg)
{
	struct rtwn_softc *sc = arg;

	rtwn_cmd_sleepable(sc, NULL, 0, r92c_handle_c2h_task);
}
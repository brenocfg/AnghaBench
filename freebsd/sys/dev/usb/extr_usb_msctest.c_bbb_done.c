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
struct bbb_transfer {int error; int status_try; int /*<<< orphan*/  cv; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_COMMAND ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbb_done(struct bbb_transfer *sc, int error)
{
	sc->error = error;
	sc->state = ST_COMMAND;
	sc->status_try = 1;
	cv_signal(&sc->cv);
}
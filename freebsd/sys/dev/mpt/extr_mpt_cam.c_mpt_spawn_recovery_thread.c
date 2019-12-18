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
struct mpt_softc {int /*<<< orphan*/  unit; int /*<<< orphan*/  recovery_thread; } ;

/* Variables and functions */
 int kproc_create (int /*<<< orphan*/ ,struct mpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_recovery_thread ; 

__attribute__((used)) static int
mpt_spawn_recovery_thread(struct mpt_softc *mpt)
{
	int error;

	error = kproc_create(mpt_recovery_thread, mpt,
	    &mpt->recovery_thread, /*flags*/0,
	    /*altstack*/0, "mpt_recovery%d", mpt->unit);
	return (error);
}
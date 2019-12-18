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
struct proc {int dummy; } ;
struct bcm2835_audio_info {int /*<<< orphan*/  worker_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORKER_RUNNING ; 
 int /*<<< orphan*/  bcm2835_audio_worker ; 
 scalar_t__ kproc_create (int /*<<< orphan*/ ,void*,struct proc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
bcm2835_audio_create_worker(struct bcm2835_audio_info *sc)
{
	struct proc *newp;

	sc->worker_state = WORKER_RUNNING;
	if (kproc_create(bcm2835_audio_worker, (void*)sc, &newp, 0, 0,
	    "bcm2835_audio_worker") != 0) {
		printf("failed to create bcm2835_audio_worker\n");
	}
}
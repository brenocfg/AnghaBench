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
struct hda_audio_ctxt {int /*<<< orphan*/  mtx; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* do_transfer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cond; int /*<<< orphan*/  run; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
hda_audio_ctxt_thr(void *arg)
{
	struct hda_audio_ctxt *actx = arg;

	DPRINTF("Start Thread: %s\n", actx->name);

	pthread_mutex_lock(&actx->mtx);
	while (1) {
		while (!actx->run)
			pthread_cond_wait(&actx->cond, &actx->mtx);

		actx->do_transfer(actx->priv);
	}
	pthread_mutex_unlock(&actx->mtx);

	pthread_exit(NULL);
	return (NULL);
}
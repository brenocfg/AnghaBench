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
struct hda_audio_ctxt {int run; int (* do_setup ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  mtx; int /*<<< orphan*/  cond; int /*<<< orphan*/  priv; struct hda_audio_ctxt* started; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct hda_audio_ctxt*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hda_audio_ctxt_start(struct hda_audio_ctxt *actx)
{
	int err = 0;

	assert(actx);
	assert(actx->started);

	/* The stream is supposed to be stopped */
	if (actx->run)
		return (-1);

	pthread_mutex_lock(&actx->mtx);
	err = (* actx->do_setup)(actx->priv);
	if (!err) {
		actx->run = 1;
		pthread_cond_signal(&actx->cond);
	}
	pthread_mutex_unlock(&actx->mtx);

	return (err);
}
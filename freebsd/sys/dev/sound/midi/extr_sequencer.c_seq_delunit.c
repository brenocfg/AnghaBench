#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct seq_softc* b; } ;
struct TYPE_3__ {struct seq_softc* b; } ;
struct seq_softc {int done; int /*<<< orphan*/  seq_lock; TYPE_2__ in_q; TYPE_1__ out_q; struct seq_softc* midi_flags; struct seq_softc* midis; int /*<<< orphan*/ * musicdev; int /*<<< orphan*/ * seqdev; int /*<<< orphan*/  th_cv; int /*<<< orphan*/  in_cv; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  reset_cv; int /*<<< orphan*/  empty_cv; int /*<<< orphan*/  state_cv; scalar_t__ playing; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct seq_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nseq ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  seqinfo_mtx ; 
 struct seq_softc** seqs ; 

__attribute__((used)) static int
seq_delunit(int unit)
{
	struct seq_softc *scp = seqs[unit];
	int i;

	//SEQ_DEBUG(4, printf("seq_delunit: %d\n", unit));
	SEQ_DEBUG(1, printf("seq_delunit: 1 \n"));
	mtx_lock(&scp->seq_lock);

	scp->playing = 0;
	scp->done = 1;
	cv_broadcast(&scp->out_cv);
	cv_broadcast(&scp->state_cv);
	cv_broadcast(&scp->reset_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 2 \n"));
	cv_wait(&scp->th_cv, &scp->seq_lock);
	SEQ_DEBUG(1, printf("seq_delunit: 3.0 \n"));
	mtx_unlock(&scp->seq_lock);
	SEQ_DEBUG(1, printf("seq_delunit: 3.1 \n"));

	cv_destroy(&scp->state_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 4 \n"));
	cv_destroy(&scp->empty_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 5 \n"));
	cv_destroy(&scp->reset_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 6 \n"));
	cv_destroy(&scp->out_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 7 \n"));
	cv_destroy(&scp->in_cv);
	SEQ_DEBUG(1, printf("seq_delunit: 8 \n"));
	cv_destroy(&scp->th_cv);

	SEQ_DEBUG(1, printf("seq_delunit: 10 \n"));
	if (scp->seqdev)
		destroy_dev(scp->seqdev);
	SEQ_DEBUG(1, printf("seq_delunit: 11 \n"));
	if (scp->musicdev)
		destroy_dev(scp->musicdev);
	SEQ_DEBUG(1, printf("seq_delunit: 12 \n"));
	scp->seqdev = scp->musicdev = NULL;
	if (scp->midis != NULL)
		free(scp->midis, M_TEMP);
	SEQ_DEBUG(1, printf("seq_delunit: 13 \n"));
	if (scp->midi_flags != NULL)
		free(scp->midi_flags, M_TEMP);
	SEQ_DEBUG(1, printf("seq_delunit: 14 \n"));
	free(scp->out_q.b, M_TEMP);
	SEQ_DEBUG(1, printf("seq_delunit: 15 \n"));
	free(scp->in_q.b, M_TEMP);

	SEQ_DEBUG(1, printf("seq_delunit: 16 \n"));

	mtx_destroy(&scp->seq_lock);
	SEQ_DEBUG(1, printf("seq_delunit: 17 \n"));
	free(scp, M_DEVBUF);

	mtx_lock(&seqinfo_mtx);
	for (i = unit; i < (nseq - 1); i++)
		seqs[i] = seqs[i + 1];
	nseq--;
	mtx_unlock(&seqinfo_mtx);

	return 0;
}
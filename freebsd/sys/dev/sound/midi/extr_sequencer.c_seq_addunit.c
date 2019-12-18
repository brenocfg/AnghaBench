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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {struct seq_softc* b; } ;
struct seq_softc {int unit; TYPE_2__ in_q; TYPE_2__ out_q; struct seq_softc* midi_flags; struct seq_softc* midis; TYPE_1__* musicdev; TYPE_1__* seqdev; int /*<<< orphan*/ * mapper; int /*<<< orphan*/  mapper_cookie; int /*<<< orphan*/  th_cv; int /*<<< orphan*/  in_cv; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  reset_cv; int /*<<< orphan*/  empty_cv; int /*<<< orphan*/  state_cv; int /*<<< orphan*/  seq_lock; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_3__ {struct seq_softc* si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EV_SZ ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MIDIMKMINOR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_INIT (TYPE_2__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_DEV_MUSIC ; 
 int /*<<< orphan*/  SND_DEV_SEQ ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  destroy_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct seq_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kproc_create (int /*<<< orphan*/ ,struct seq_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 void* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * midimapper_addseq (struct seq_softc*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nseq ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  seq_cdevsw ; 
 int /*<<< orphan*/  seq_eventthread ; 
 int /*<<< orphan*/  seqinfo_mtx ; 
 struct seq_softc** seqs ; 
 int /*<<< orphan*/  sequencer_class ; 

__attribute__((used)) static int
seq_addunit(void)
{
	struct seq_softc *scp;
	int ret;
	u_char *buf;

	/* Allocate the softc. */
	ret = ENOMEM;
	scp = malloc(sizeof(*scp), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (scp == NULL) {
		SEQ_DEBUG(1, printf("seq_addunit: softc allocation failed.\n"));
		goto err;
	}
	kobj_init((kobj_t)scp, &sequencer_class);

	buf = malloc(sizeof(*buf) * EV_SZ * 1024, M_TEMP, M_NOWAIT | M_ZERO);
	if (buf == NULL)
		goto err;
	MIDIQ_INIT(scp->in_q, buf, EV_SZ * 1024);
	buf = malloc(sizeof(*buf) * EV_SZ * 1024, M_TEMP, M_NOWAIT | M_ZERO);
	if (buf == NULL)
		goto err;
	MIDIQ_INIT(scp->out_q, buf, EV_SZ * 1024);
	ret = EINVAL;

	scp->midis = malloc(sizeof(kobj_t) * 32, M_TEMP, M_NOWAIT | M_ZERO);
	scp->midi_flags = malloc(sizeof(*scp->midi_flags) * 32, M_TEMP,
	    M_NOWAIT | M_ZERO);

	if (scp->midis == NULL || scp->midi_flags == NULL)
		goto err;

	scp->flags = 0;

	mtx_init(&scp->seq_lock, "seqflq", NULL, 0);
	cv_init(&scp->state_cv, "seqstate");
	cv_init(&scp->empty_cv, "seqempty");
	cv_init(&scp->reset_cv, "seqtimer");
	cv_init(&scp->out_cv, "seqqout");
	cv_init(&scp->in_cv, "seqqin");
	cv_init(&scp->th_cv, "seqstart");

	/*
	 * Init the damn timer
	 */

	scp->mapper = midimapper_addseq(scp, &scp->unit, &scp->mapper_cookie);
	if (scp->mapper == NULL)
		goto err;

	scp->seqdev = make_dev(&seq_cdevsw,
	    MIDIMKMINOR(scp->unit, SND_DEV_SEQ, 0), UID_ROOT,
	    GID_WHEEL, 0666, "sequencer%d", scp->unit);

	scp->musicdev = make_dev(&seq_cdevsw,
	    MIDIMKMINOR(scp->unit, SND_DEV_MUSIC, 0), UID_ROOT,
	    GID_WHEEL, 0666, "music%d", scp->unit);

	if (scp->seqdev == NULL || scp->musicdev == NULL)
		goto err;
	/*
	 * TODO: Add to list of sequencers this module provides
	 */

	ret =
	    kproc_create
	    (seq_eventthread, scp, NULL, RFHIGHPID, 0,
	    "sequencer %02d", scp->unit);

	if (ret)
		goto err;

	scp->seqdev->si_drv1 = scp->musicdev->si_drv1 = scp;

	SEQ_DEBUG(2, printf("sequencer %d created scp %p\n", scp->unit, scp));

	ret = 0;

	mtx_lock(&seqinfo_mtx);
	seqs[nseq++] = scp;
	mtx_unlock(&seqinfo_mtx);

	goto ok;

err:
	if (scp != NULL) {
		if (scp->seqdev != NULL)
			destroy_dev(scp->seqdev);
		if (scp->musicdev != NULL)
			destroy_dev(scp->musicdev);
		/*
	         * TODO: Destroy mutex and cv
	         */
		if (scp->midis != NULL)
			free(scp->midis, M_TEMP);
		if (scp->midi_flags != NULL)
			free(scp->midi_flags, M_TEMP);
		if (scp->out_q.b)
			free(scp->out_q.b, M_TEMP);
		if (scp->in_q.b)
			free(scp->in_q.b, M_TEMP);
		free(scp, M_DEVBUF);
	}
ok:
	return ret;
}
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
struct mqueue {scalar_t__ mq_curmsgs; scalar_t__ mq_maxmsg; int /*<<< orphan*/  mq_mutex; } ;
struct knote {int /*<<< orphan*/  kn_fp; } ;

/* Variables and functions */
 struct mqueue* FPTOMQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_mqwrite(struct knote *kn, long hint)
{
	struct mqueue *mq = FPTOMQ(kn->kn_fp);

	mtx_assert(&mq->mq_mutex, MA_OWNED);
	return (mq->mq_curmsgs < mq->mq_maxmsg);
}
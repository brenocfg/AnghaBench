#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_rr_queue {int /*<<< orphan*/  q_seekdist; int /*<<< orphan*/  q_thinktime; } ;
struct bio {scalar_t__ bio_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  w_anticipate; int /*<<< orphan*/  wait_ms; } ;

/* Variables and functions */
 scalar_t__ BIO_WRITE ; 
 int g_savg_read (int /*<<< orphan*/ *) ; 
 scalar_t__ g_savg_valid (int /*<<< orphan*/ *) ; 
 int get_bounded (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ me ; 

__attribute__((used)) static inline int
g_rr_should_anticipate(struct g_rr_queue *qp, struct bio *bp)
{
	int wait = get_bounded(&me.wait_ms, 2);

	if (!me.w_anticipate && (bp->bio_cmd == BIO_WRITE))
		return (0);

	if (g_savg_valid(&qp->q_thinktime) &&
	    g_savg_read(&qp->q_thinktime) > wait)
		return (0);

	if (g_savg_valid(&qp->q_seekdist) &&
	    g_savg_read(&qp->q_seekdist) > 8192)
		return (0);

	return (1);
}
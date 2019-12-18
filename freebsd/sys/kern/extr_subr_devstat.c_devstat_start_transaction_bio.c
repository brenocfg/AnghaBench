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
struct devstat {int dummy; } ;
struct bio {int /*<<< orphan*/  bio_t0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_DEVSTAT_BIO_START () ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_mutex ; 
 int /*<<< orphan*/  devstat_start_transaction (struct devstat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devstat_start_transaction_bio(struct devstat *ds, struct bio *bp)
{

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	/* sanity check */
	if (ds == NULL)
		return;

	binuptime(&bp->bio_t0);
	devstat_start_transaction(ds, &bp->bio_t0);
	DTRACE_DEVSTAT_BIO_START();
}
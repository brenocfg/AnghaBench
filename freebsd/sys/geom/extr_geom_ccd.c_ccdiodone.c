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
struct bio {scalar_t__ bio_cmd; scalar_t__ bio_error; int /*<<< orphan*/  bio_inbed; struct bio* bio_caller1; int /*<<< orphan*/  bio_from; struct bio* bio_parent; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_std_done (struct bio*) ; 

__attribute__((used)) static void
ccdiodone(struct bio *cbp)
{
	struct bio *mbp, *pbp;

	mbp = cbp->bio_caller1;
	pbp = cbp->bio_parent;

	if (pbp->bio_cmd == BIO_READ) {
		if (cbp->bio_error == 0) {
			/* We will not be needing the partner bio */
			if (mbp != NULL) {
				pbp->bio_inbed++;
				g_destroy_bio(mbp);
			}
			g_std_done(cbp);
			return;
		}
		if (mbp != NULL) {
			/* Try partner the bio instead */
			mbp->bio_caller1 = NULL;
			pbp->bio_inbed++;
			g_destroy_bio(cbp);
			g_io_request(mbp, mbp->bio_from);
			/*
			 * XXX: If this comes back OK, we should actually
			 * try to write the good data on the failed mirror
			 */
			return;
		}
		g_std_done(cbp);
		return;
	}
	if (mbp != NULL) {
		mbp->bio_caller1 = NULL;
		pbp->bio_inbed++;
		if (cbp->bio_error != 0 && pbp->bio_error == 0)
			pbp->bio_error = cbp->bio_error;
		g_destroy_bio(cbp);
		return;
	}
	g_std_done(cbp);
}
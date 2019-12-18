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
struct bio {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; scalar_t__ bio_resid; } ;
struct aac_command {TYPE_1__* cm_fib; scalar_t__ cm_private; } ;
struct aac_blockwrite_response {scalar_t__ Status; } ;
struct aac_blockread_response {scalar_t__ Status; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
typedef  scalar_t__ AAC_FSAStatus ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ST_OK ; 
 int /*<<< orphan*/  aac_biodone (struct bio*) ; 
 int /*<<< orphan*/  aac_release_command (struct aac_command*) ; 

__attribute__((used)) static void
aac_bio_complete(struct aac_command *cm)
{
	struct aac_blockread_response *brr;
	struct aac_blockwrite_response *bwr;
	struct bio *bp;
	AAC_FSAStatus status;

	/* fetch relevant status and then release the command */
	bp = (struct bio *)cm->cm_private;
	if (bp->bio_cmd == BIO_READ) {
		brr = (struct aac_blockread_response *)&cm->cm_fib->data[0];
		status = brr->Status;
	} else {
		bwr = (struct aac_blockwrite_response *)&cm->cm_fib->data[0];
		status = bwr->Status;
	}
	aac_release_command(cm);

	/* fix up the bio based on status */
	if (status == ST_OK) {
		bp->bio_resid = 0;
	} else {
		bp->bio_error = EIO;
		bp->bio_flags |= BIO_ERROR;
	}
	aac_biodone(bp);
}
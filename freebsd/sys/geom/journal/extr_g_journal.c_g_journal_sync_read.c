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
struct g_consumer {TYPE_1__* provider; } ;
struct bio {void* bio_data; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/ * bio_done; int /*<<< orphan*/  bio_cmd; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int biowait (struct bio*,char*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 

__attribute__((used)) static int
g_journal_sync_read(struct g_consumer *cp, struct bio *bp, off_t offset,
    void *data)
{
	int error;

	g_reset_bio(bp);
	bp->bio_cmd = BIO_READ;
	bp->bio_done = NULL;
	bp->bio_offset = offset;
	bp->bio_length = cp->provider->sectorsize;
	bp->bio_data = data;
	g_io_request(bp, cp);
	error = biowait(bp, "gjs_read");
	return (error);
}
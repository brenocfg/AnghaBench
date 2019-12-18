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
struct bio {void* bio_data; scalar_t__ bio_length; scalar_t__ bio_offset; int /*<<< orphan*/ * bio_done; int /*<<< orphan*/  bio_cmd; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_2__ {scalar_t__ sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MAXPHYS ; 
 int biowait (struct bio*,char*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 

int
g_write_data(struct g_consumer *cp, off_t offset, void *ptr, off_t length)
{
	struct bio *bp;
	int error;

	KASSERT(length > 0 && length >= cp->provider->sectorsize &&
	    length <= MAXPHYS, ("g_write_data(): invalid length %jd",
	    (intmax_t)length));

	bp = g_alloc_bio();
	bp->bio_cmd = BIO_WRITE;
	bp->bio_done = NULL;
	bp->bio_offset = offset;
	bp->bio_length = length;
	bp->bio_data = ptr;
	g_io_request(bp, cp);
	error = biowait(bp, "gwrite");
	g_destroy_bio(bp);
	return (error);
}
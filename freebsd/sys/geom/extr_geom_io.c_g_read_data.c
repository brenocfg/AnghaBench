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
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MAXPHYS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int biowait (struct bio*,char*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 void* g_malloc (scalar_t__,int /*<<< orphan*/ ) ; 

void *
g_read_data(struct g_consumer *cp, off_t offset, off_t length, int *error)
{
	struct bio *bp;
	void *ptr;
	int errorc;

	KASSERT(length > 0 && length >= cp->provider->sectorsize &&
	    length <= MAXPHYS, ("g_read_data(): invalid length %jd",
	    (intmax_t)length));

	bp = g_alloc_bio();
	bp->bio_cmd = BIO_READ;
	bp->bio_done = NULL;
	bp->bio_offset = offset;
	bp->bio_length = length;
	ptr = g_malloc(length, M_WAITOK);
	bp->bio_data = ptr;
	g_io_request(bp, cp);
	errorc = biowait(bp, "gread");
	if (error != NULL)
		*error = errorc;
	g_destroy_bio(bp);
	if (errorc) {
		g_free(ptr);
		ptr = NULL;
	}
	return (ptr);
}
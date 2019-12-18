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
struct g_consumer {int dummy; } ;
struct bio {char const* bio_attribute; int bio_length; int bio_completed; void* bio_data; int /*<<< orphan*/ * bio_done; int /*<<< orphan*/  bio_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_GETATTR ; 
 int /*<<< orphan*/  G_T_BIO ; 
 int biowait (struct bio*,char*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,char const*) ; 

int
g_io_getattr(const char *attr, struct g_consumer *cp, int *len, void *ptr)
{
	struct bio *bp;
	int error;

	g_trace(G_T_BIO, "bio_getattr(%s)", attr);
	bp = g_alloc_bio();
	bp->bio_cmd = BIO_GETATTR;
	bp->bio_done = NULL;
	bp->bio_attribute = attr;
	bp->bio_length = *len;
	bp->bio_data = ptr;
	g_io_request(bp, cp);
	error = biowait(bp, "ggetattr");
	*len = bp->bio_completed;
	g_destroy_bio(bp);
	return (error);
}
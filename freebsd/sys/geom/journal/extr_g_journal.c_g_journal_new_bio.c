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
typedef  int /*<<< orphan*/  u_char ;
struct bio {void* bio_length; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_cmd; void* bio_joffset; void* bio_offset; } ;
typedef  void* off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_journal_std_done ; 
 int /*<<< orphan*/ * gj_malloc (void*,int) ; 

__attribute__((used)) static struct bio *
g_journal_new_bio(off_t start, off_t end, off_t joffset, u_char *data,
    int flags)
{
	struct bio *bp;

	bp = g_alloc_bio();
	bp->bio_offset = start;
	bp->bio_joffset = joffset;
	bp->bio_length = end - start;
	bp->bio_cmd = BIO_WRITE;
	bp->bio_done = g_journal_std_done;
	if (data == NULL)
		bp->bio_data = NULL;
	else {
		bp->bio_data = gj_malloc(bp->bio_length, flags);
		if (bp->bio_data != NULL)
			bcopy(data, bp->bio_data, bp->bio_length);
	}
	return (bp);
}
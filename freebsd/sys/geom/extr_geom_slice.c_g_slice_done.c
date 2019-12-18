#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bio {scalar_t__ bio_cmd; scalar_t__ bio_error; char* bio_data; int /*<<< orphan*/  bio_length; TYPE_2__* bio_parent; int /*<<< orphan*/  bio_attribute; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_4__ {TYPE_1__* bio_to; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 scalar_t__ BIO_GETATTR ; 
 scalar_t__ EFAULT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_std_done (struct bio*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_slice_done(struct bio *bp)
{

	KASSERT(bp->bio_cmd == BIO_GETATTR &&
	    strcmp(bp->bio_attribute, "GEOM::ident") == 0,
	    ("bio_cmd=0x%x bio_attribute=%s", bp->bio_cmd, bp->bio_attribute));

	if (bp->bio_error == 0 && bp->bio_data[0] != '\0') {
		char idx[8];

		/* Add index to the ident received. */
		snprintf(idx, sizeof(idx), "s%d",
		    bp->bio_parent->bio_to->index);
		if (strlcat(bp->bio_data, idx, bp->bio_length) >=
		    bp->bio_length) {
			bp->bio_error = EFAULT;
		}
	}
	g_std_done(bp);
}
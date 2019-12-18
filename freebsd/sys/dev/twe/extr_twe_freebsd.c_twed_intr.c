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
struct bio {int bio_flags; scalar_t__ bio_resid; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  TWED_BIO_OUT ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

void
twed_intr(struct bio *bp)
{
    debug_called(4);

    /* if no error, transfer completed */
    if (!(bp->bio_flags & BIO_ERROR))
	bp->bio_resid = 0;

    biodone(bp);
    TWED_BIO_OUT;
}
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
struct bio {int bio_flags; scalar_t__ bio_resid; int /*<<< orphan*/  bio_error; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  debug (int,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

void
amrd_intr(void *data)
{
    struct bio *bio = (struct bio *)data;

    debug_called(2);

    if (bio->bio_flags & BIO_ERROR) {
	bio->bio_error = EIO;
	debug(1, "i/o error\n");
    } else {
	bio->bio_resid = 0;
    }

    biodone(bio);
}
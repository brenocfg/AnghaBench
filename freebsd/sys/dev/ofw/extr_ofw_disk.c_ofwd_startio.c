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
typedef  scalar_t__ u_int ;
struct ofwd_softc {int /*<<< orphan*/  ofwd_instance; } ;
struct bio {int bio_cmd; scalar_t__ bio_length; scalar_t__ bio_resid; scalar_t__ bio_data; int /*<<< orphan*/  bio_offset; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 scalar_t__ OF_read (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ OF_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_write (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ofwd_startio(struct ofwd_softc *sc, struct bio *bp)
{
	u_int r;

	r = OF_seek(sc->ofwd_instance, bp->bio_offset);

	switch (bp->bio_cmd) {
	case BIO_READ:
		r = OF_read(sc->ofwd_instance, (void *)bp->bio_data,
		   bp->bio_length);
		break;
	case BIO_WRITE:
		r = OF_write(sc->ofwd_instance, (void *)bp->bio_data,
		   bp->bio_length);
		break;
	}
	if (r != bp->bio_length)
		panic("ofwd: incorrect i/o count");

	bp->bio_resid = 0;
	return (0);
}
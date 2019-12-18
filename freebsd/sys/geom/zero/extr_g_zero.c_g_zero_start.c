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
struct bio {int bio_cmd; int bio_flags; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_completed; int /*<<< orphan*/  bio_data; } ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
 int BIO_UNMAPPED ; 
#define  BIO_WRITE 128 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  g_zero_byte ; 
 int /*<<< orphan*/  g_zero_clear ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_zero_start(struct bio *bp)
{
	int error = ENXIO;

	switch (bp->bio_cmd) {
	case BIO_READ:
		if (g_zero_clear && (bp->bio_flags & BIO_UNMAPPED) == 0)
			memset(bp->bio_data, g_zero_byte, bp->bio_length);
		/* FALLTHROUGH */
	case BIO_DELETE:
	case BIO_WRITE:
		bp->bio_completed = bp->bio_length;
		error = 0;
		break;
	case BIO_GETATTR:
	default:
		error = EOPNOTSUPP;
		break;
	}
	g_io_deliver(bp, error);
}
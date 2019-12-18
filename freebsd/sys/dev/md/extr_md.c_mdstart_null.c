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
struct md_s {int dummy; } ;
struct bio {int bio_cmd; scalar_t__ bio_resid; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_data; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_flush_dcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mdstart_null(struct md_s *sc, struct bio *bp)
{

	switch (bp->bio_cmd) {
	case BIO_READ:
		bzero(bp->bio_data, bp->bio_length);
		cpu_flush_dcache(bp->bio_data, bp->bio_length);
		break;
	case BIO_WRITE:
		break;
	}
	bp->bio_resid = 0;
	return (0);
}
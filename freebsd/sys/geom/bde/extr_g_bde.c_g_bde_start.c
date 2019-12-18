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
struct bio {int bio_cmd; } ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  g_bde_start1 (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_bde_start(struct bio *bp)
{

	switch (bp->bio_cmd) {
	case BIO_DELETE:
	case BIO_READ:
	case BIO_WRITE:
		g_bde_start1(bp);
		break;
	case BIO_GETATTR:
		g_io_deliver(bp, EOPNOTSUPP);
		break;
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		return;
	}
	return;
}
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
struct disk {int /*<<< orphan*/  d_maxsize; int /*<<< orphan*/  d_delmaxsize; } ;
struct bio {scalar_t__ bio_cmd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 

__attribute__((used)) static off_t
g_disk_maxsize(struct disk *dp, struct bio *bp)
{
	if (bp->bio_cmd == BIO_DELETE)
		return (dp->d_delmaxsize);
	return (dp->d_maxsize);
}
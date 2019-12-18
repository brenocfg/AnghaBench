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
struct bio {int /*<<< orphan*/  bi_partno; int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */
 char const* disk_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

const char *bio_devname(struct bio *bio, char *buf)
{
	return disk_name(bio->bi_disk, bio->bi_partno, buf);
}
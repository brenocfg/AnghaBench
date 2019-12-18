#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bio {scalar_t__ bio_cmd; scalar_t__ bio_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  gs_write_bytes_in_flight; int /*<<< orphan*/  gs_writes_in_flight; int /*<<< orphan*/  gs_bytes_in_flight; int /*<<< orphan*/  gs_in_flight; int /*<<< orphan*/  gs_done; } ;

/* Variables and functions */
 scalar_t__ BIO_WRITE ; 
 TYPE_1__ me ; 

__attribute__((used)) static void
g_sched_update_stats(struct bio *bio)
{

	me.gs_done++;
	me.gs_in_flight--;
	me.gs_bytes_in_flight -= bio->bio_length;
	if (bio->bio_cmd == BIO_WRITE) {
		me.gs_writes_in_flight--;
		me.gs_write_bytes_in_flight -= bio->bio_length;
	}
}
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
struct rb0_cbdata {int drive; int /*<<< orphan*/  complete; } ;
struct bio {scalar_t__ bi_status; scalar_t__ bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_OPEN_SHOULD_FAIL_BIT ; 
 TYPE_1__* UDRS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void floppy_rb0_cb(struct bio *bio)
{
	struct rb0_cbdata *cbdata = (struct rb0_cbdata *)bio->bi_private;
	int drive = cbdata->drive;

	if (bio->bi_status) {
		pr_info("floppy: error %d while reading block 0\n",
			bio->bi_status);
		set_bit(FD_OPEN_SHOULD_FAIL_BIT, &UDRS->flags);
	}
	complete(&cbdata->complete);
}
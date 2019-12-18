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
struct devstat {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devstat_end_transaction_bio_bt (struct devstat*,struct bio const*,int /*<<< orphan*/ *) ; 

void
devstat_end_transaction_bio(struct devstat *ds, const struct bio *bp)
{

	devstat_end_transaction_bio_bt(ds, bp, NULL);
}
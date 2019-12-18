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
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __end_block_io_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 

__attribute__((used)) static void end_block_io_op(struct bio *bio)
{
	__end_block_io_op(bio->bi_private, bio->bi_status);
	bio_put(bio);
}
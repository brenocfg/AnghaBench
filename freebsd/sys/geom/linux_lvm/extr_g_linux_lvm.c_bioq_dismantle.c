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
struct bio_queue_head {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bioq_first (struct bio_queue_head*) ; 
 int /*<<< orphan*/  bioq_remove (struct bio_queue_head*,struct bio*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 

__attribute__((used)) static void
bioq_dismantle(struct bio_queue_head *bq)
{
	struct bio *b;

	for (b = bioq_first(bq); b != NULL; b = bioq_first(bq)) {
		bioq_remove(bq, b);
		g_destroy_bio(b);
	}
}
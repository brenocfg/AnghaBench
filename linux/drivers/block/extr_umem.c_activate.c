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
struct cardinfo {int Active; size_t Ready; TYPE_1__* mm_pages; } ;
struct TYPE_2__ {scalar_t__ cnt; } ;

/* Variables and functions */
 scalar_t__ add_bio (struct cardinfo*) ; 
 int /*<<< orphan*/  mm_start_io (struct cardinfo*) ; 

__attribute__((used)) static void activate(struct cardinfo *card)
{
	/* if No page is Active, and Ready is
	 * not empty, then switch Ready page
	 * to active and start IO.
	 * Then add any bh's that are available to Ready
	 */

	do {
		while (add_bio(card))
			;

		if (card->Active == -1 &&
		    card->mm_pages[card->Ready].cnt > 0) {
			card->Active = card->Ready;
			card->Ready = 1-card->Ready;
			mm_start_io(card);
		}

	} while (card->Active == -1 && add_bio(card));
}
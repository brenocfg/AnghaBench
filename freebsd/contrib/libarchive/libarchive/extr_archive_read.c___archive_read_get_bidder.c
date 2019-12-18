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
struct archive_read_filter_bidder {int /*<<< orphan*/ * bid; } ;
struct archive_read {int /*<<< orphan*/  archive; struct archive_read_filter_bidder* bidders; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct archive_read_filter_bidder*,int /*<<< orphan*/ ,int) ; 

int
__archive_read_get_bidder(struct archive_read *a,
    struct archive_read_filter_bidder **bidder)
{
	int i, number_slots;

	number_slots = sizeof(a->bidders) / sizeof(a->bidders[0]);

	for (i = 0; i < number_slots; i++) {
		if (a->bidders[i].bid == NULL) {
			memset(a->bidders + i, 0, sizeof(a->bidders[0]));
			*bidder = (a->bidders + i);
			return (ARCHIVE_OK);
		}
	}

	archive_set_error(&a->archive, ENOMEM,
	    "Not enough slots for filter registration");
	return (ARCHIVE_FATAL);
}
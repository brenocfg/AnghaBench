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
struct links_entry {unsigned int links; struct archive_entry* canonical; } ;
struct archive_entry_linkresolver {TYPE_1__* spare; } ;
struct archive_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  canonical; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT_ENTRY_PARTIAL ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct links_entry* next_entry (struct archive_entry_linkresolver*,int /*<<< orphan*/ ) ; 

struct archive_entry *
archive_entry_partial_links(struct archive_entry_linkresolver *res,
    unsigned int *links)
{
	struct archive_entry	*e;
	struct links_entry	*le;

	/* Free a held entry. */
	if (res->spare != NULL) {
		archive_entry_free(res->spare->canonical);
		archive_entry_free(res->spare->entry);
		free(res->spare);
		res->spare = NULL;
	}

	le = next_entry(res, NEXT_ENTRY_PARTIAL);
	if (le != NULL) {
		e = le->canonical;
		if (links != NULL)
			*links = le->links;
		le->canonical = NULL;
	} else {
		e = NULL;
		if (links != NULL)
			*links = 0;
	}
	return (e);
}
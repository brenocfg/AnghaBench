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
struct unrhdr {int /*<<< orphan*/  head; scalar_t__ len; int /*<<< orphan*/  last; struct unrhdr* ptr; int /*<<< orphan*/  first; } ;
struct unrb {int /*<<< orphan*/  head; scalar_t__ len; int /*<<< orphan*/  last; struct unrb* ptr; int /*<<< orphan*/  first; } ;
struct unr {int /*<<< orphan*/  head; scalar_t__ len; int /*<<< orphan*/  last; struct unr* ptr; int /*<<< orphan*/  first; } ;

/* Variables and functions */
 struct unrhdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct unrhdr* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct unrhdr* TAILQ_NEXT (struct unrhdr*,int /*<<< orphan*/ ) ; 
 struct unrhdr* TAILQ_PREV (struct unrhdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct unrhdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_unr (struct unrhdr*,struct unrhdr*) ; 
 scalar_t__ is_bitmap (struct unrhdr*,struct unrhdr*) ; 
 int /*<<< orphan*/  list ; 
 scalar_t__ optimize_unr (struct unrhdr*) ; 
 scalar_t__ ub_empty (struct unrhdr*,scalar_t__) ; 
 scalar_t__ ub_full (struct unrhdr*,scalar_t__) ; 
 int /*<<< orphan*/  unrhd ; 

__attribute__((used)) static void
collapse_unr(struct unrhdr *uh, struct unr *up)
{
	struct unr *upp;
	struct unrb *ub;

	/* If bitmap is all set or clear, change it to runlength */
	if (is_bitmap(uh, up)) {
		ub = up->ptr;
		if (ub_full(ub, up->len)) {
			delete_unr(uh, up->ptr);
			up->ptr = uh;
		} else if (ub_empty(ub, up->len)) {
			delete_unr(uh, up->ptr);
			up->ptr = NULL;
		}
	}

	/* If nothing left in runlength, delete it */
	if (up->len == 0) {
		upp = TAILQ_PREV(up, unrhd, list);
		if (upp == NULL)
			upp = TAILQ_NEXT(up, list);
		TAILQ_REMOVE(&uh->head, up, list);
		delete_unr(uh, up);
		up = upp;
	}

	/* If we have "hot-spot" still, merge with neighbor if possible */
	if (up != NULL) {
		upp = TAILQ_PREV(up, unrhd, list);
		if (upp != NULL && up->ptr == upp->ptr) {
			up->len += upp->len;
			TAILQ_REMOVE(&uh->head, upp, list);
			delete_unr(uh, upp);
			}
		upp = TAILQ_NEXT(up, list);
		if (upp != NULL && up->ptr == upp->ptr) {
			up->len += upp->len;
			TAILQ_REMOVE(&uh->head, upp, list);
			delete_unr(uh, upp);
		}
	}

	/* Merge into ->first if possible */
	upp = TAILQ_FIRST(&uh->head);
	if (upp != NULL && upp->ptr == uh) {
		uh->first += upp->len;
		TAILQ_REMOVE(&uh->head, upp, list);
		delete_unr(uh, upp);
		if (up == upp)
			up = NULL;
	}

	/* Merge into ->last if possible */
	upp = TAILQ_LAST(&uh->head, unrhd);
	if (upp != NULL && upp->ptr == NULL) {
		uh->last += upp->len;
		TAILQ_REMOVE(&uh->head, upp, list);
		delete_unr(uh, upp);
		if (up == upp)
			up = NULL;
	}

	/* Try to make bitmaps */
	while (optimize_unr(uh))
		continue;
}
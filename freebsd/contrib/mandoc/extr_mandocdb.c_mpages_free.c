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
struct mpage {struct mpage* desc; struct mpage* title; struct mpage* arch; struct mpage* sec; struct mpage* next; struct mlink* mlinks; } ;
struct mlink {struct mlink* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mpage*) ; 
 int /*<<< orphan*/  mlink_free (struct mlink*) ; 
 struct mpage* mpage_head ; 

__attribute__((used)) static void
mpages_free(void)
{
	struct mpage	*mpage;
	struct mlink	*mlink;

	while ((mpage = mpage_head) != NULL) {
		while ((mlink = mpage->mlinks) != NULL) {
			mpage->mlinks = mlink->next;
			mlink_free(mlink);
		}
		mpage_head = mpage->next;
		free(mpage->sec);
		free(mpage->arch);
		free(mpage->title);
		free(mpage->desc);
		free(mpage);
	}
}
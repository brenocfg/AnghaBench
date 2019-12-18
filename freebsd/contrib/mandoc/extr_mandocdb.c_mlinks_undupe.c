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
struct mpage {scalar_t__ form; struct mlink* mlinks; } ;
struct mlink {scalar_t__ dform; struct mlink* next; int /*<<< orphan*/  file; int /*<<< orphan*/  dsec; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ FORM_CAT ; 
 scalar_t__ FORM_NONE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mlink_free (struct mlink*) ; 
 int /*<<< orphan*/  mlinks ; 
 int /*<<< orphan*/ * ohash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohash_qlookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  say (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ use_all ; 
 scalar_t__ warnings ; 

__attribute__((used)) static void
mlinks_undupe(struct mpage *mpage)
{
	char		  buf[PATH_MAX];
	struct mlink	**prev;
	struct mlink	 *mlink;
	char		 *bufp;

	mpage->form = FORM_CAT;
	prev = &mpage->mlinks;
	while (NULL != (mlink = *prev)) {
		if (FORM_CAT != mlink->dform) {
			mpage->form = FORM_NONE;
			goto nextlink;
		}
		(void)strlcpy(buf, mlink->file, sizeof(buf));
		bufp = strstr(buf, "cat");
		assert(NULL != bufp);
		memcpy(bufp, "man", 3);
		if (NULL != (bufp = strrchr(buf, '.')))
			*++bufp = '\0';
		(void)strlcat(buf, mlink->dsec, sizeof(buf));
		if (NULL == ohash_find(&mlinks,
		    ohash_qlookup(&mlinks, buf)))
			goto nextlink;
		if (warnings)
			say(mlink->file, "Man source exists: %s", buf);
		if (use_all)
			goto nextlink;
		*prev = mlink->next;
		mlink_free(mlink);
		continue;
nextlink:
		prev = &(*prev)->next;
	}
}
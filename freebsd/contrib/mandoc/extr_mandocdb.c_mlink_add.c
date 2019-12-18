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
struct stat {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
struct mpage {char* dsec; char* arch; char* name; char* fsec; struct mpage* mpage; struct mpage* mlinks; struct mpage* next; void* form; TYPE_1__ inodev; int /*<<< orphan*/ * file; void* fform; } ;
struct mlink {char* dsec; char* arch; char* name; char* fsec; struct mlink* mpage; struct mlink* mlinks; struct mlink* next; void* form; TYPE_1__ inodev; int /*<<< orphan*/ * file; void* fform; } ;
struct inodev {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
typedef  int /*<<< orphan*/  inodev ;

/* Variables and functions */
 void* FORM_CAT ; 
 void* FORM_NONE ; 
 void* FORM_SRC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct mpage* mandoc_calloc (int,int) ; 
 void* mandoc_strdup (char*) ; 
 int /*<<< orphan*/  memset (struct inodev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlinks ; 
 struct mpage* mpage_head ; 
 int /*<<< orphan*/  mpages ; 
 struct mpage* ohash_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ohash_insert (int /*<<< orphan*/ *,unsigned int,struct mpage*) ; 
 unsigned int ohash_lookup_memory (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 unsigned int ohash_qlookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlink_add(struct mlink *mlink, const struct stat *st)
{
	struct inodev	 inodev;
	struct mpage	*mpage;
	unsigned int	 slot;

	assert(NULL != mlink->file);

	mlink->dsec = mandoc_strdup(mlink->dsec ? mlink->dsec : "");
	mlink->arch = mandoc_strdup(mlink->arch ? mlink->arch : "");
	mlink->name = mandoc_strdup(mlink->name ? mlink->name : "");
	mlink->fsec = mandoc_strdup(mlink->fsec ? mlink->fsec : "");

	if ('0' == *mlink->fsec) {
		free(mlink->fsec);
		mlink->fsec = mandoc_strdup(mlink->dsec);
		mlink->fform = FORM_CAT;
	} else if ('1' <= *mlink->fsec && '9' >= *mlink->fsec)
		mlink->fform = FORM_SRC;
	else
		mlink->fform = FORM_NONE;

	slot = ohash_qlookup(&mlinks, mlink->file);
	assert(NULL == ohash_find(&mlinks, slot));
	ohash_insert(&mlinks, slot, mlink);

	memset(&inodev, 0, sizeof(inodev));  /* Clear padding. */
	inodev.st_ino = st->st_ino;
	inodev.st_dev = st->st_dev;
	slot = ohash_lookup_memory(&mpages, (char *)&inodev,
	    sizeof(struct inodev), inodev.st_ino);
	mpage = ohash_find(&mpages, slot);
	if (NULL == mpage) {
		mpage = mandoc_calloc(1, sizeof(struct mpage));
		mpage->inodev.st_ino = inodev.st_ino;
		mpage->inodev.st_dev = inodev.st_dev;
		mpage->form = FORM_NONE;
		mpage->next = mpage_head;
		mpage_head = mpage;
		ohash_insert(&mpages, slot, mpage);
	} else
		mlink->next = mpage->mlinks;
	mpage->mlinks = mlink;
	mlink->mpage = mpage;
}
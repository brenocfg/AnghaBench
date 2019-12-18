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
struct tag_entry {scalar_t__ prio; size_t nlines; char* s; struct tag_entry* lines; } ;
struct TYPE_2__ {int tfd; char* ofn; char* tfn; int /*<<< orphan*/ * tagname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_FDOPEN ; 
 int /*<<< orphan*/  MANDOCERR_TAG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,struct tag_entry) ; 
 int /*<<< orphan*/  free (struct tag_entry*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohash_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ohash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tag_entry* ohash_first (int /*<<< orphan*/ *,unsigned int*) ; 
 struct tag_entry* ohash_next (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  ohash_qlookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_data ; 
 TYPE_1__ tag_files ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
tag_write(void)
{
	FILE			*stream;
	struct tag_entry	*entry;
	size_t			 i;
	unsigned int		 slot;
	int			 empty;

	if (tag_files.tfd <= 0)
		return;
	if (tag_files.tagname != NULL && ohash_find(&tag_data,
            ohash_qlookup(&tag_data, tag_files.tagname)) == NULL) {
		mandoc_msg(MANDOCERR_TAG, 0, 0, "%s", tag_files.tagname);
		tag_files.tagname = NULL;
	}
	if ((stream = fdopen(tag_files.tfd, "w")) == NULL)
		mandoc_msg(MANDOCERR_FDOPEN, 0, 0, "%s", strerror(errno));
	empty = 1;
	entry = ohash_first(&tag_data, &slot);
	while (entry != NULL) {
		if (stream != NULL && entry->prio >= 0) {
			for (i = 0; i < entry->nlines; i++) {
				fprintf(stream, "%s %s %zu\n",
				    entry->s, tag_files.ofn, entry->lines[i]);
				empty = 0;
			}
		}
		free(entry->lines);
		free(entry);
		entry = ohash_next(&tag_data, &slot);
	}
	ohash_delete(&tag_data);
	if (stream != NULL)
		fclose(stream);
	else
		close(tag_files.tfd);
	tag_files.tfd = -1;
	if (empty) {
		unlink(tag_files.tfn);
		*tag_files.tfn = '\0';
	}
}
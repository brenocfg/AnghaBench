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
struct archive_entry_linkresolver {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFDIR ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_USTAR ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_hardlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_linkify (struct archive_entry_linkresolver*,struct archive_entry**,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_entry_linkresolver_free (struct archive_entry_linkresolver*) ; 
 struct archive_entry_linkresolver* archive_entry_linkresolver_new () ; 
 int /*<<< orphan*/  archive_entry_linkresolver_set_strategy (struct archive_entry_linkresolver*,int /*<<< orphan*/ ) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_dev (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_hardlink (struct archive_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_set_ino (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_linkify_tar(void)
{
	struct archive_entry *entry, *e2;
	struct archive_entry_linkresolver *resolver;

	/* Initialize the resolver. */
	assert(NULL != (resolver = archive_entry_linkresolver_new()));
	archive_entry_linkresolver_set_strategy(resolver,
	    ARCHIVE_FORMAT_TAR_USTAR);

	/* Create an entry with only 1 link and try to linkify it. */
	assert(NULL != (entry = archive_entry_new()));
	archive_entry_set_pathname(entry, "test1");
	archive_entry_set_ino(entry, 1);
	archive_entry_set_dev(entry, 2);
	archive_entry_set_nlink(entry, 1);
	archive_entry_set_size(entry, 10);
	archive_entry_linkify(resolver, &entry, &e2);

	/* Shouldn't have been changed. */
	assert(e2 == NULL);
	assertEqualInt(10, archive_entry_size(entry));
	assertEqualString("test1", archive_entry_pathname(entry));

	/* Now, try again with an entry that has 2 links. */
	archive_entry_set_pathname(entry, "test2");
	archive_entry_set_nlink(entry, 2);
	archive_entry_set_ino(entry, 2);
	archive_entry_linkify(resolver, &entry, &e2);
	/* Shouldn't be altered, since it wasn't seen before. */
	assert(e2 == NULL);
	assertEqualString("test2", archive_entry_pathname(entry));
	assertEqualString(NULL, archive_entry_hardlink(entry));
	assertEqualInt(10, archive_entry_size(entry));

	/* Match again and make sure it does get altered. */
	archive_entry_linkify(resolver, &entry, &e2);
	assert(e2 == NULL);
	assertEqualString("test2", archive_entry_pathname(entry));
	assertEqualString("test2", archive_entry_hardlink(entry));
	assertEqualInt(0, archive_entry_size(entry));


	/* Dirs should never be matched as hardlinks, regardless. */
	archive_entry_set_pathname(entry, "test3");
	archive_entry_set_nlink(entry, 2);
	archive_entry_set_filetype(entry, AE_IFDIR);
	archive_entry_set_ino(entry, 3);
	archive_entry_set_hardlink(entry, NULL);
	archive_entry_linkify(resolver, &entry, &e2);
	/* Shouldn't be altered, since it wasn't seen before. */
	assert(e2 == NULL);
	assertEqualString("test3", archive_entry_pathname(entry));
	assertEqualString(NULL, archive_entry_hardlink(entry));

	/* Dir, so it shouldn't get matched. */
	archive_entry_linkify(resolver, &entry, &e2);
	assert(e2 == NULL);
	assertEqualString("test3", archive_entry_pathname(entry));
	assertEqualString(NULL, archive_entry_hardlink(entry));

	archive_entry_free(entry);
	archive_entry_linkresolver_free(resolver);
}
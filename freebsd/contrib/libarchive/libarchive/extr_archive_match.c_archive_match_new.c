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
struct archive {int /*<<< orphan*/  state; int /*<<< orphan*/  magic; } ;
struct archive_match {int recursive_include; struct archive archive; int /*<<< orphan*/  now; int /*<<< orphan*/  inclusion_gnames; int /*<<< orphan*/  inclusion_unames; int /*<<< orphan*/  exclusion_entry_list; int /*<<< orphan*/  exclusion_tree; int /*<<< orphan*/  exclusions; int /*<<< orphan*/  inclusions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_MATCH_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  __archive_rb_tree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  entry_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_ops_mbs ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

struct archive *
archive_match_new(void)
{
	struct archive_match *a;

	a = (struct archive_match *)calloc(1, sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->archive.magic = ARCHIVE_MATCH_MAGIC;
	a->archive.state = ARCHIVE_STATE_NEW;
	a->recursive_include = 1;
	match_list_init(&(a->inclusions));
	match_list_init(&(a->exclusions));
	__archive_rb_tree_init(&(a->exclusion_tree), &rb_ops_mbs);
	entry_list_init(&(a->exclusion_entry_list));
	match_list_init(&(a->inclusion_unames));
	match_list_init(&(a->inclusion_gnames));
	time(&a->now);
	return (&(a->archive));
}
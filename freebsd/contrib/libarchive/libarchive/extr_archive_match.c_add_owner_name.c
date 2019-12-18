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
struct match_list {int dummy; } ;
struct match {int /*<<< orphan*/  pattern; } ;
struct archive_match {int /*<<< orphan*/  setflag; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ID_IS_SET ; 
 int /*<<< orphan*/  archive_mstring_copy_mbs (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  archive_mstring_copy_wcs (int /*<<< orphan*/ *,void const*) ; 
 struct match* calloc (int,int) ; 
 int error_nomem (struct archive_match*) ; 
 int /*<<< orphan*/  match_list_add (struct match_list*,struct match*) ; 

__attribute__((used)) static int
add_owner_name(struct archive_match *a, struct match_list *list,
    int mbs, const void *name)
{
	struct match *match;

	match = calloc(1, sizeof(*match));
	if (match == NULL)
		return (error_nomem(a));
	if (mbs)
		archive_mstring_copy_mbs(&(match->pattern), name);
	else
		archive_mstring_copy_wcs(&(match->pattern), name);
	match_list_add(list, match);
	a->setflag |= ID_IS_SET;
	return (ARCHIVE_OK);
}
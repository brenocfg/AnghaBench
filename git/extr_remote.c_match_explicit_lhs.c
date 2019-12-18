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
struct refspec_item {int /*<<< orphan*/  src; } ;
struct ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int count_refspec_match (int /*<<< orphan*/ ,struct ref*,struct ref**) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_explicit_object_name (int /*<<< orphan*/ ,struct ref**) ; 

__attribute__((used)) static int match_explicit_lhs(struct ref *src,
			      struct refspec_item *rs,
			      struct ref **match,
			      int *allocated_match)
{
	switch (count_refspec_match(rs->src, src, match)) {
	case 1:
		if (allocated_match)
			*allocated_match = 0;
		return 0;
	case 0:
		/* The source could be in the get_sha1() format
		 * not a reference name.  :refs/other is a
		 * way to delete 'other' ref at the remote end.
		 */
		if (try_explicit_object_name(rs->src, match) < 0)
			return error(_("src refspec %s does not match any"), rs->src);
		if (allocated_match)
			*allocated_match = 1;
		return 0;
	default:
		return error(_("src refspec %s matches more than one"), rs->src);
	}
}
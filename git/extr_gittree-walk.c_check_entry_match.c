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

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 int name_compare (char const*,int,char const*,int) ; 

__attribute__((used)) static int check_entry_match(const char *a, int a_len, const char *b, int b_len)
{
	/*
	 * The caller wants to pick *a* from a tree or nothing.
	 * We are looking at *b* in a tree.
	 *
	 * (0) If a and b are the same name, we are trivially happy.
	 *
	 * There are three possibilities where *a* could be hiding
	 * behind *b*.
	 *
	 * (1) *a* == "t",   *b* == "ab"  i.e. *b* sorts earlier than *a* no
	 *                                matter what.
	 * (2) *a* == "t",   *b* == "t-2" and "t" is a subtree in the tree;
	 * (3) *a* == "t-2", *b* == "t"   and "t-2" is a blob in the tree.
	 *
	 * Otherwise we know *a* won't appear in the tree without
	 * scanning further.
	 */

	int cmp = name_compare(a, a_len, b, b_len);

	/* Most common case first -- reading sync'd trees */
	if (!cmp)
		return cmp;

	if (0 < cmp) {
		/* a comes after b; it does not matter if it is case (3)
		if (b_len < a_len && !memcmp(a, b, b_len) && a[b_len] < '/')
			return 1;
		*/
		return 1; /* keep looking */
	}

	/* b comes after a; are we looking at case (2)? */
	if (a_len < b_len && !memcmp(a, b, a_len) && b[a_len] < '/')
		return 1; /* keep looking */

	return -1; /* a cannot appear in the tree */
}
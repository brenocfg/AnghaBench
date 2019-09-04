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
typedef  int /*<<< orphan*/  uintmax_t ;
struct tree_entry {int dummy; } ;

/* Variables and functions */
 int GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  do_change_note_fanout (struct tree_entry*,struct tree_entry*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static uintmax_t change_note_fanout(struct tree_entry *root,
		unsigned char fanout)
{
	/*
	 * The size of path is due to one slash between every two hex digits,
	 * plus the terminating NUL.  Note that there is no slash at the end, so
	 * the number of slashes is one less than half the number of hex
	 * characters.
	 */
	char hex_oid[GIT_MAX_HEXSZ], path[GIT_MAX_HEXSZ + (GIT_MAX_HEXSZ / 2) - 1 + 1];
	return do_change_note_fanout(root, root, hex_oid, 0, path, 0, fanout);
}
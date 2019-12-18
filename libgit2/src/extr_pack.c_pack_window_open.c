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
struct TYPE_2__ {int fd; int size; } ;
struct git_pack_file {TYPE_1__ mwf; } ;
typedef  int git_off_t ;
typedef  int /*<<< orphan*/  git_mwindow ;

/* Variables and functions */
 unsigned char* git_mwindow_open (TYPE_1__*,int /*<<< orphan*/ **,int,int,unsigned int*) ; 
 scalar_t__ packfile_open (struct git_pack_file*) ; 

__attribute__((used)) static unsigned char *pack_window_open(
		struct git_pack_file *p,
		git_mwindow **w_cursor,
		git_off_t offset,
		unsigned int *left)
{
	if (p->mwf.fd == -1 && packfile_open(p) < 0)
		return NULL;

	/* Since packfiles end in a hash of their content and it's
	 * pointless to ask for an offset into the middle of that
	 * hash, and the pack_window_contains function above wouldn't match
	 * don't allow an offset too close to the end of the file.
	 *
	 * Don't allow a negative offset, as that means we've wrapped
	 * around.
	 */
	if (offset > (p->mwf.size - 20))
		return NULL;
	if (offset < 0)
		return NULL;

	return git_mwindow_open(&p->mwf, w_cursor, offset, 20, left);
 }
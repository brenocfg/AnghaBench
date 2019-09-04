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
struct git_pack_file {int pack_local; scalar_t__ mtime; } ;

/* Variables and functions */

__attribute__((used)) static int packfile_sort__cb(const void *a_, const void *b_)
{
	const struct git_pack_file *a = a_;
	const struct git_pack_file *b = b_;
	int st;

	/*
	 * Local packs tend to contain objects specific to our
	 * variant of the project than remote ones. In addition,
	 * remote ones could be on a network mounted filesystem.
	 * Favor local ones for these reasons.
	 */
	st = a->pack_local - b->pack_local;
	if (st)
		return -st;

	/*
	 * Younger packs tend to contain more recent objects,
	 * and more recent objects tend to get accessed more
	 * often.
	 */
	if (a->mtime < b->mtime)
		return 1;
	else if (a->mtime == b->mtime)
		return 0;

	return -1;
}
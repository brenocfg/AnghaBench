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
struct diff_options {int /*<<< orphan*/  prefix_length; scalar_t__ prefix; } ;
struct diff_filespec {int dummy; } ;
struct diff_filepair {int is_unmerged; } ;

/* Variables and functions */
 struct diff_filespec* alloc_filespec (char const*) ; 
 struct diff_filepair* diff_queue (int /*<<< orphan*/ *,struct diff_filespec*,struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_queued_diff ; 
 scalar_t__ strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

struct diff_filepair *diff_unmerge(struct diff_options *options, const char *path)
{
	struct diff_filepair *pair;
	struct diff_filespec *one, *two;

	if (options->prefix &&
	    strncmp(path, options->prefix, options->prefix_length))
		return NULL;

	one = alloc_filespec(path);
	two = alloc_filespec(path);
	pair = diff_queue(&diff_queued_diff, one, two);
	pair->is_unmerged = 1;
	return pair;
}
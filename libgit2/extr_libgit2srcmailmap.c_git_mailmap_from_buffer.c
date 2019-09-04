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
typedef  int /*<<< orphan*/  git_mailmap ;

/* Variables and functions */
 int /*<<< orphan*/  git_mailmap_free (int /*<<< orphan*/ *) ; 
 int git_mailmap_new (int /*<<< orphan*/ **) ; 
 int mailmap_add_buffer (int /*<<< orphan*/ *,char const*,size_t) ; 

int git_mailmap_from_buffer(git_mailmap **out, const char *data, size_t len)
{
	int error = git_mailmap_new(out);
	if (error < 0)
		return error;

	error = mailmap_add_buffer(*out, data, len);
	if (error < 0) {
		git_mailmap_free(*out);
		*out = NULL;
	}
	return error;
}
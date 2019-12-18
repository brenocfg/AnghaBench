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
struct commit_extra_header {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 char* get_commit_buffer (struct commit*,unsigned long*) ; 
 struct commit_extra_header* read_commit_extra_header_lines (char const*,unsigned long,char const**) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

struct commit_extra_header *read_commit_extra_headers(struct commit *commit,
						      const char **exclude)
{
	struct commit_extra_header *extra = NULL;
	unsigned long size;
	const char *buffer = get_commit_buffer(commit, &size);
	extra = read_commit_extra_header_lines(buffer, size, exclude);
	unuse_commit_buffer(commit, buffer);
	return extra;
}
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
struct cmt_fmt_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_formats ; 
 struct cmt_fmt_map* find_commit_format_recursive (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_commit_formats () ; 

__attribute__((used)) static struct cmt_fmt_map *find_commit_format(const char *sought)
{
	if (!commit_formats)
		setup_commit_formats();

	return find_commit_format_recursive(sought, sought, 0);
}
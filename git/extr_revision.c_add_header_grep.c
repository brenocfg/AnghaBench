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
struct rev_info {int /*<<< orphan*/  grep_filter; } ;
typedef  enum grep_header_field { ____Placeholder_grep_header_field } grep_header_field ;

/* Variables and functions */
 int /*<<< orphan*/  append_header_grep_pattern (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void add_header_grep(struct rev_info *revs, enum grep_header_field field, const char *pattern)
{
	append_header_grep_pattern(&revs->grep_filter, field, pattern);
}
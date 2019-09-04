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
struct rev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREP_PATTERN_BODY ; 
 int /*<<< orphan*/  add_grep (struct rev_info*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_message_grep(struct rev_info *revs, const char *pattern)
{
	add_grep(revs, pattern, GREP_PATTERN_BODY);
}
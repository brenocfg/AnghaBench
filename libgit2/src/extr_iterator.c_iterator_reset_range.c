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
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  iterator_range_free (int /*<<< orphan*/ *) ; 
 int iterator_range_init (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int iterator_reset_range(
	git_iterator *iter, const char *start, const char *end)
{
	iterator_range_free(iter);
	return iterator_range_init(iter, start, end);
}
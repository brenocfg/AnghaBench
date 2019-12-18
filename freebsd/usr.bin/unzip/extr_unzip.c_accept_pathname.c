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

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exclude ; 
 int /*<<< orphan*/  include ; 
 scalar_t__ match_pattern (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
accept_pathname(const char *pathname)
{

	if (!STAILQ_EMPTY(&include) && !match_pattern(&include, pathname))
		return (0);
	if (!STAILQ_EMPTY(&exclude) && match_pattern(&exclude, pathname))
		return (0);
	return (1);
}
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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_strategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_strategy (char const*) ; 

__attribute__((used)) static int option_parse_strategy(const struct option *opt,
				 const char *name, int unset)
{
	if (unset)
		return 0;

	append_strategy(get_strategy(name));
	return 0;
}